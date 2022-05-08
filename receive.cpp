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

#ifdef __cplusplus
}
#endif

using namespace cv;
using namespace std;

int main()
{
    //接收的图片大小
    Mat image(Size(640, 480), CV_8U, Scalar(0, 0, 0));

    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr)); //每个字节都用0填充
    serv_addr.sin_family = AF_INET;           //使用IPv4地址
    serv_addr.sin_addr.s_addr = INADDR_ANY;   //具体的IP地址
    serv_addr.sin_port = htons(12345);        //端口
    // long optval = 1024 * 1024 * 2;
    // socklen_t optlen = sizeof(long);
    // setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &optval, optlen);

    // if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0)
    // {
    //     printf("connect ok\n");
    // }
    // else
    // {
    //     perror("Error:");
    // }
    // long nowoptval = 0;
    // optlen = sizeof(nowoptval);
    // getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &nowoptval, &optlen);
    // printf("%ldk\n", nowoptval / 1024);

    // while (1)
    // {
    //     recv(sock, image.data, image.total() * image.channels(), MSG_WAITALL);
    //     imshow("b", image);
    //     waitKey(20);
    // }
    socklen_t nSize = sizeof(serv_addr);
    char buffer[20];
    sendto(sock, buffer, 10, 0, (struct sockaddr *)&serv_addr, nSize);
    size_t count = 0;
    unsigned long frame_num=0;

    while (1)
    {
        // UDP不保证传送可靠性，这里用一个特殊包使发送端和接收端图像对齐
        if (recvfrom(sock, buffer, 20, 0, (struct sockaddr *)&serv_addr, &nSize) == 10)
        {
            for (int i = 0; i < 480; i++)
            {
                count = count + recvfrom(sock, image.row(i).data, 640, 0, (struct sockaddr *)&serv_addr, &nSize);
            }
            if(count==307200)
            {
                imshow("b", image);
                waitKey(20);
                frame_num++;
                cout<<frame_num<<endl;
            }
            count = 0;
        }
    }

    close(sock);

    waitKey(0);

    return 0;
}