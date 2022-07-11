#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, const char *argv[])
{
    int sock;
    struct sockaddr_in recv_adr;

    if (argc != 3)
    {
        printf("Usage: %s <IP> <port> \n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error");
    memset(&recv_adr, 0, sizeof(recv_adr));
    recv_adr.sin_family = AF_INET;
    recv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    recv_adr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&recv_adr, sizeof(recv_adr)) == -1)
        error_handling("connect() error");

    //发送紧急消息,Lunix上是信号处理(事件驱动)，Windows上可以select函数模拟
    write(sock, "123", strlen("123"));
    send(sock, "4", strlen("4"), MSG_OOB);
    sleep(2); // os上紧急消息同时发送，下一条会替换上一条，同一时间只能保存一条(可能是一个变量保存的，不是缓冲数组)
    write(sock, "567", strlen("567"));
    send(sock, "890", strlen("890"), MSG_OOB);

    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}