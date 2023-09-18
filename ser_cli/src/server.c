#include "common.h"
#define BUFFER_SIZE 1024

void handle_client(int client_sock) {
    char buffer[BUFFER_SIZE + 1];
    int n;

    while (1) {
        memset(buffer, 0, BUFFER_SIZE + 1);
        n = receive_data(client_sock, buffer, BUFFER_SIZE);
        if (n <= 0) {
            if (n == 0) {
                printf("Client disconnected.\n");
            } else {
                perror("Error reading from socket");
            }
            close(client_sock);
            exit(0);
        }

        printf("Received: %s", buffer);
        send_data(client_sock, buffer); // echo back to the client
    }
}

int main(int argc, char *argv[]) {

    int sockfd, newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    int portno = atoi(argv[1]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(1);
    }

    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);


    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error on binding");
        exit(1);
    }

    // got default number from 
    listen(sockfd, 100);
    clilen = sizeof(cli_addr);

    printf("got address info, listening");

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0) {
            perror("Error on accept");
            continue;
        }

        printf("Connection from %s:%d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

        pid_t pid = fork();
        if (pid == 0) { // child
            close(sockfd); // child doesn't need the listening socket
            handle_client(newsockfd);
        } else {
            perror("fork error");
        }
    }

    close(sockfd);
    return 0;
}
