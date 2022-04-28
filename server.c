#include "stdlib.h"
#include "stdio.h"
#include "arpa/inet.h"
#include "netinet/in.h"
#include "sys/socket.h"
#include "unistd.h"
#include "string.h"
#include "server.h"

int server_init()       //套接字初始化
{
    //新建套接字
    int serverfd = socket(AF_INET, SOCK_STREAM, 0);

    //填充套接字属性
    struct sockaddr_in seraddr;
    memset(&seraddr, 0, sizeof(seraddr));
    seraddr.sin_addr.s_addr = INADDR_ANY;
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(1234);
    //绑定套接字
    int bindnum=bind(serverfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    if(bindnum==-1)//绑定失败
    {
        perror("Error:");
        return -1;
    }
    printf("bindnum:%d\n",bindnum);
    long optval=1024*1024*2;
    socklen_t optlen=sizeof(optval);
    setsockopt(serverfd,SOL_SOCKET,SO_SNDBUF,&optval,optlen);//设置发送缓冲区大小，可能超过内核规定大小，此时需要改内核设置
    listen(serverfd, 20);
    printf("start listen\n");

    return serverfd;

}


//发送函数
//sock_fd发送所用套接字描述符，data指向数据包头部的指针，data_len数据大小
int mysend(int sock_fd,const unsigned char* data,unsigned long data_len)
{
    unsigned char *ptr = (unsigned char *)data;
    ssize_t sendsize = 0;

    while (sendsize != data_len)
    {
        ssize_t temp = write(sock_fd, ptr, data_len);
        if (temp != -1)
        {
            sendsize = sendsize + temp;
            ptr = ptr + data_len;
        }
        temp = 0;
    }

    return 0;
}