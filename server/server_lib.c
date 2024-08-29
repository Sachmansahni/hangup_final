// server_lib.c
#include "server_lib.h"

static int sockfd, newsockfd;
static struct sockaddr_in serv_addr, cli_addr;
static socklen_t clilen;
static char buffer[255];

void setup_server(int port) {
    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR OPENING SOCKET");
        exit(1);
    }

    // Zero out the structure and set the values
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    // Bind the socket
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR ON BINDING");
        exit(1);
    }

    // Listen for incoming connections
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    // Accept an incoming connection
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0) {
        perror("ERROR ON ACCEPT");
        exit(1);
    }
}

void run_server() {
    int n;

    while (1) {
        // Clear the buffer and receive data from the client
        memset(buffer, 0, 255);
        n = recv(newsockfd, buffer, 255, 0);
        if (n < 0) {
            perror("ERROR ON READING");
            exit(1);
        }
        printf("Client: %s", buffer);

        // Clear the buffer and read data from stdin
        memset(buffer, 0, 255);
        fgets(buffer, 255, stdin);

        // Send the data to the client
        n = send(newsockfd, buffer, strlen(buffer), 0);
        if (n < 0) {
            perror("ERROR ON WRITING");
            exit(1);
        }

        // Exit the loop if the message is "Bye"
        if (strcmp("Bye\n", buffer) == 0) {
            break;
        }
    }

    // Close the sockets
    close(newsockfd);
    close(sockfd);
}
