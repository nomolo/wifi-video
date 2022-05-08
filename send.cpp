#include "opencv2/opencv.hpp"
#include <iostream>
#include "server.h"
#include "librealsense2/rs.hpp"

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
    // VideoCapture capture("1.mp4");
    // Mat image;

    // Create a Pipeline - this serves as a top-level API for streaming and processing frames
    // rs2::pipeline p;

    // rs2::config pipe_config;
    // pipe_config.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 60); //设置数据信息
    // p.start(pipe_config);

    // rs2::frameset frames = p.wait_for_frames();
    // auto color = frames.get_color_frame();
    // const int w = color.get_width();
    // const int h = color.get_height();
    VideoCapture capture(0);
    Mat image;
    capture>>image;
    const int w = image.cols;
    const int h = image.rows;

    int server_fd = server_udp_init();
    if (server_fd == -1)
    {
        return -1;
    }

    // struct sockaddr_in cliaddr;
    // socklen_t clnt_addr_size = sizeof(cliaddr);
    // int clientfd = accept(server_fd, (struct sockaddr *)&cliaddr, &clnt_addr_size); //等待连接

    // printf("connect\n");
    int num = 0;

    sockaddr cliaddr;
    socklen_t nSize = sizeof(cliaddr);
    char buffer[10];
    recvfrom(server_fd,buffer,10,0,&cliaddr,&nSize);

    while(1)
    {
        capture>>image;
        // frames = p.wait_for_frames();
        // color = frames.get_color_frame();
        // Mat image(Size(w, h), CV_8UC3, (void *)color.get_data(), Mat::AUTO_STEP);
        cvtColor(image,image,COLOR_BGR2GRAY);
        imshow("a",image);
        waitKey(20);
        mysend_udp(server_fd,image.data,image.total()* image.channels(),&cliaddr);
        num++;
        cout<<num<<endl;
    }
    

    // while (1)
    // {
    //     frames = p.wait_for_frames();
    //     color = frames.get_color_frame();
    //     Mat image(Size(w, h), CV_8UC3, (void *)color.get_data(), Mat::AUTO_STEP);
    //     cvtColor(image,image,COLOR_BGR2GRAY);
    //     imshow("a",image);
    //     waitKey(20);
    //     // for (int i = 0; i < (image.rows/2); i++)
    //     // {
    //     //     mysend(clientfd, image.row(i).data, 2*image.cols* image.channels());
    //     // }
    //     mysend(clientfd, image.data, image.total()* image.channels());
    //     num++;
    //     cout << num << endl;
    // }

    // shutdown(clientfd, SHUT_WR);
    // shutdown(server_fd, SHUT_WR);
    // close(clientfd);
    close(server_fd);

    

    return 0;
}