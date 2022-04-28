#include "opencv2/opencv.hpp"
#include <iostream>

#ifdef __cplusplus
extern "C"
{
#endif

#include "stdlib.h"
#include "stdio.h"
#include "arpa/inet.h"
#include "netinet/in.h"
#include "sys/socket.h"
#include "unistd.h"
#include "string.h"
#include "server.h"

#ifdef __cplusplus
}
#endif

using namespace cv;
using namespace std;

int main()
{
    Mat image(Size(720,1280),CV_8UC3,Scalar(0,0,0));

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));           //每个字节都用0填充
    serv_addr.sin_family = AF_INET;                     //使用IPv4地址
    serv_addr.sin_addr.s_addr = INADDR_ANY; //具体的IP地址
    serv_addr.sin_port = htons(1234);                  //端口
    long optval=1024*1024*2;
    socklen_t optlen=sizeof(long);
    setsockopt(sock,SOL_SOCKET,SO_RCVBUF,&optval,optlen);


    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0)
    {
        printf("connect ok\n");
    }
    else
    {
        perror("Error:");
    }
    long nowoptval=0;
    optlen=sizeof(nowoptval);
    getsockopt(sock,SOL_SOCKET,SO_RCVBUF,&nowoptval,&optlen);
    printf("%ldk\n",nowoptval/1024);

    while(1)
    {
    recv(sock,image.data, image.total()*image.channels(),MSG_WAITALL);
    imshow("b", image);
    waitKey(20);
    }

    close(sock);

    waitKey(0);

    return 0;
}