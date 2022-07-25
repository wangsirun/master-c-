#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <semaphore.h>
#include <mutex>
#include <list>
// info centos g++ -std=c++11 sql.cpp $(mysql_config --cflags --libs) -g -lpthread -o sql
// info ubuntu mysqlpool.cpp -o mysqltest -lmysqlclient -g -lpthread

using namespace std;

class mysqlpool
{
private:
    /* data */
    int freeNum = 0;
    int userNum = 0;
    sem_t reserve;
    mutex lock;
    list<MYSQL *> connList; //连接池

public:
    mysqlpool(string, int, string, string, string);
    void init(int max_conn);
    MYSQL *getconn();
    bool ReleaseConnection(MYSQL *);
    list<string> query(string query);
    ~mysqlpool();

public:
    string m_url;          //主机地址
    int m_Port;            //数据库端口号
    string m_User;         //登陆数据库用户名
    string m_PassWord;     //登陆数据库密码
    string m_DatabaseName; //使用数据库名
};

mysqlpool::mysqlpool(string url, int port, string user, string passwd, string databaseName) : m_url(url), m_Port(port), m_User(user), m_PassWord(passwd), m_DatabaseName(databaseName)
{
    cout << "init config success" << endl;
}

list<string> mysqlpool::query(string query)
{
    list<string> res;
    MYSQL *mysql = getconn();
    if (mysql_query(mysql, query.c_str()))
    {
        cout << mysql_error(mysql) << endl;
        // LOG_ERROR("SELECT error:%s\n", mysql_error(mysql));
    }

    MYSQL_RES *result = mysql_store_result(mysql);

    int num_fields = mysql_num_fields(result);

    MYSQL_FIELD *fields = mysql_fetch_fields(result);

    while (MYSQL_ROW row = mysql_fetch_row(result))
    {
        for (size_t i = 0; i < num_fields; i++)
        {
            res.push_back(string(row[i]));
        }
    }
    ReleaseConnection(mysql);
    return res;
}

MYSQL *mysqlpool::getconn()
{
    sem_wait(&reserve);
    lock.lock();
    MYSQL *res = connList.front();
    connList.pop_front();
    --freeNum;
    ++userNum;
    lock.unlock();
    return res;
}

bool mysqlpool::ReleaseConnection(MYSQL *con)
{
    if (con == nullptr)
    {
        return false;
    }
    lock.lock();
    connList.push_back(con);
    ++freeNum;
    --userNum;

    lock.unlock();
    cout << "del conn to pool" << endl;

    sem_post(&reserve);
    return true;
}

void mysqlpool::init(int max_conn)
{
    for (size_t i = 0; i < max_conn; i++)
    {
        /* code */
        MYSQL *conn = nullptr;
        conn = mysql_init(conn);

        if (conn == NULL)
        {
            cout << "mysql init error" << endl;
            exit(1);
        }
        conn = mysql_real_connect(conn, m_url.c_str(), m_User.c_str(), m_PassWord.c_str(), m_DatabaseName.c_str(), m_Port, NULL, 0);

        if (conn == NULL)
        {
            cout << "mysql init error" << endl;
            exit(1);
        }
        connList.push_back(conn);
        ++freeNum;
    }
    // 初始化信号量
    sem_init(&reserve, 0, freeNum);
}

mysqlpool::~mysqlpool()
{
    lock.lock();
    if (connList.size() > 0)
    {
        list<MYSQL *>::iterator it;
        for (it = connList.begin(); it != connList.end(); ++it)
        {
            MYSQL *con = *it;
            mysql_close(con);
        }
        freeNum = 0;
        userNum = 0;
        connList.clear();
    }

    lock.unlock();
}

int main(int argc, char const *argv[])
{
    /* code */
    mysqlpool pool = {"localhost", 3306, "root", "root", "db_content"};
    pool.init(8);
    for (size_t i = 0; i < 1000; i++)
    {
        list<string> res = pool.query("select * from user");
    }

    list<string> res = pool.query("select * from user");
    for (auto &&i : res)
    {
        cout << i << endl;
    }
    return 0;
}
