#include "common.h"

#define BUFFER_SIZE 1024
#define CHAR_PER_READ 1

static int read_cnt;
static char *read_ptr;
static char read_buf[BUFFER_SIZE];

//Read functions from W. Richard Stevens, Bill Fenner, and Andrew M. Rudoff, Unix Network
//Programming, Volume 1, The Sockets Networking API, 3rd Edition, Addison- Wesley,
//2004, Chapter 3.


static ssize_t my_read(int fd, char *ptr) {
    if (read_cnt <= 0) {
    again:
        if ((read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) {
            if (errno == EINTR)
                goto again;
            return (-1);
        } else if (read_cnt == 0)
            return (0);
        read_ptr = read_buf;
    }
    read_cnt--;
    *ptr = *read_ptr++;
    return (1);
}

ssize_t readLine(int fd, void *vptr, size_t maxlen) {
    ssize_t n, rc;
    char c, *ptr;

    ptr = vptr;
    for (n = 1; n < maxlen; n++) {
        if ((rc = my_read(fd, &c)) == 1) {
            *ptr++ = c;
            if (c == '\n')
                break; /* newline is stored, like fgets() */
        } else if (rc == 0) {
            *ptr = 0;
            return (n - 1); /* EOF, n - 1 bytes were read */
        } else
            return (-1); /* error, errno set by read() */
    }
    *ptr = 0; /* null terminate like fgets() */
    return (n);
}

/*ssize_t readlinebuf(void **vptrptr) {
    if (read_cnt)
        *vptrptr = read_ptr;
    return (read_cnt);
}*/

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