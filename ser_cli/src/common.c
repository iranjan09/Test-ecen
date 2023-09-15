#include "common.h"

int writen(int fd, char *buf, int bufSize) {
  
  int nleft = bufSize; 
  int nwritten;

  const char *ptr = (const char*)buf;

  while (nleft > 0) {
    if ((nwritten = write(fd, buf, nleft)) < 0) {
      if (nwritten < 0 && errno == EINTR) {
        nwritten = 0; 
      }
      else {
        return -1; 
      }
    }

    nleft -= nwritten;
    buf += nwritten;
  }

  return bufSize;
}

int send_data(int sockfd, char *data) {

	int len, ret;

	// Get data length
	len = strlen(data);

	// Send data
	ret = writen(sockfd, data, len);

	// Error handling
	if (ret < 0) {
		perror("Send failed");
	}

	return ret;

}

int receive_data(int sockfd, char *buffer, int buf_size) {

	int ret;

	// Receive data
	ret = readLine(sockfd, buffer, buf_size);

	// Error handling
	if (ret < 0) {
		perror("Receive failed");
	}

	return ret;

}