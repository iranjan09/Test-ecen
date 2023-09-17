#include "common.h"

int server_sock_init(struct sockaddr_in *sockaddr, char *ip_addr, int port) {

	memset (sockaddr, 0, sizeof(*sockaddr));
	sockaddr->sin_family = AF_INET;
	sockaddr->sin_port = htons (port);

    if(inet_pton(AF_INET, ip_addr, &(sockaddr->sin_addr)) < 0) {
		perror("inet_pton error");
		return -1;
	}

    return 0;
}

int main(int argc, char *argv[]) {

	int sockfd = -1;
	int ret;
	char ip_addr[16], send_buf[BUFFER_SIZE], recv_buf[BUFFER_SIZE+1];
	struct sockaddr_in serv_sockaddr;
    int port = -1;

    // Input validation
	if (argc != 3) {
		printf("Usage: %s <ip_addr> <port>\n", argv[0]);
		return -1;
	}

	strcpy(ip_addr, argv[1]);
	port = atoi(argv[2]);
  
	printf ("Client: Server Port number is %s \n", argv[2]);
	printf ("Client: Server IPv4 Address is %s \n", argv[1]);
	
    // Unable to create socket, exit
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket error");
		exit(1);
	}
	
	if(server_sock_init(&serv_sockaddr, ip_addr, port) < 0) {
		perror("server socket init failed");
		exit(1);
	}
	
	// Connect to server
	if(connect(sockfd, (struct sockaddr*)&serv_sockaddr, sizeof(serv_sockaddr)) < 0) {
		perror("Connect Error");
		exit(1);
	}

	printf("Client connected to server\n");

	// Client communication loop
	while(1) {
	  
		memset (send_buf, 0, BUFFER_SIZE);
		memset (recv_buf, 0, BUFFER_SIZE + 1);
		// Read input from user
		fgets(send_buf, BUFFER_SIZE, stdin);
	
		if (strlen (send_buf) == 0) {
			printf("Close the connection to Server because No data/EOF\n");
			close(sockfd);
			exit(0);
		}

		// Send line to server
		if(send_data(sockfd, send_buf) < 0) {
			perror ("ERROR: Client failed to send data to server");
			break;
		}
		
		ret = receive_data(sockfd, recv_buf, BUFFER_SIZE-1);
        if (ret <= 0) {
            if (ret == 0) {
                printf("Server disconnected.\n");
            } else {
                perror("Error reading from socket");
            }
            close(sockfd);
            exit(0);
        }
		else
		{	
        recv_buf [ret] = '\0';
		}
		ret = 0;
		printf ("CLIENT Receiving data from server: %s \n", recv_buf);
  		

	}

	// Close socket
	close(sockfd);

	return 0;
}
