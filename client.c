#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "client.h"

int myrecv(unsigned char* const data,unsigned long data_len)
{
    //创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));           //每个字节都用0填充
    serv_addr.sin_family = AF_INET;                     //使用IPv4地址
    serv_addr.sin_addr.s_addr = INADDR_ANY; //具体的IP地址
    serv_addr.sin_port = htons(1234);                  //端口
    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0)
    {
        printf("connect ok\n");
    }
    else
    {
        perror("Error:");
    }

    int num=recv(sock, data, data_len,MSG_WAITALL);

    printf("num:%d\n",num);

    //关闭套接字
    close(sock);

    return 0;
}