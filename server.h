#ifndef __SERVER_H
#define __SERVER_H

#ifdef __cplusplus
extern "C"{
#endif

int server_init();
int server_udp_init();
int mysend(int sock_fd,const unsigned char* data,unsigned long data_len);
int mysend_udp(int sock_fd,const unsigned char* data,unsigned long data_len,const struct sockaddr* _addr);

#ifdef __cplusplus
}
#endif



#endif