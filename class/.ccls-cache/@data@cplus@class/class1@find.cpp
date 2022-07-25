#include <iostream>
#include <string.h>
#include <string>

using namespace std;

namespace
{
    enum METHOD : short
    {
        GET,
        POST
    };
} // namespace

int main(int argc, char const *argv[])
{
    METHOD m_method;
    string text = "POST / HTTP/1.1";
    // string text = "GET / HTTP/1.1";
    int res = text.find_first_of(" \t");
    cout << res << endl;
    string s = text.substr(0, res - 1);
    cout << s << endl;
    string left = text.substr(res);
    cout << left << endl;
    int ss = left.find_last_of("//");
    string version = left.substr(ss + 1);
    cout << version << endl;
    // m_url += strspn(m_url, " \t");
    // m_version = strpbrk(m_url, " \t");
    // if (!m_version)
    //     return BAD_REQUEST;
    // *m_version++ = '\0';
    // m_version += strspn(m_version, " \t");
    // if (strcasecmp(m_version, "HTTP/1.1") != 0)
    //     return BAD_REQUEST;
    // if (strncasecmp(m_url, "http://", 7) == 0)
    // {
    //     m_url += 7;
    //     m_url = strchr(m_url, '/');
    // }
    return 0;
}
