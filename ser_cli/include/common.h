#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int writen(int fd, char *buf, int bufSize);
int readLine (int iSocket_fd, char *pcBuffer, int iBufferSize);
int send_data(int sockfd, char *data);
int receive_data(int sockfd, char *buffer, int buf_size) 