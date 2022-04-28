#include "opencv2/opencv.hpp"
#include <iostream>
#include "server.h"

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
    VideoCapture capture("1.mp4");
    Mat image;

    int server_fd = server_init();
    if (server_fd == -1)
    {
        return -1;
    }

    struct sockaddr_in cliaddr;
    socklen_t clnt_addr_size = sizeof(cliaddr);
    int clientfd = accept(server_fd, (struct sockaddr *)&cliaddr, &clnt_addr_size);//等待连接

    printf("connect\n");
    int num=0;

    while (1)
    {
        capture >> image;
        mysend(clientfd, image.data, image.total() * image.channels());
        num++;
        cout<<num<<endl;
    }

    shutdown(clientfd, SHUT_WR);
    shutdown(server_fd, SHUT_WR);
    close(clientfd);
    close(server_fd);

    return 0;
}