// server_lib.c
#include "server_lib.h"
#include<sys/types.h>

static int sockfd, newsockfd;
static struct sockaddr_in serv_addr, cli_addr;
static socklen_t clilen;
static char buffer[255];

void setup_server(int port) {
    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);         //returns a file descriptor in integer format   //AF_INET=> IPV4  
    if (sockfd < 0) {
        perror("ERROR OPENING SOCKET");
        exit(1);
    }


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
    listen(sockfd, 5);     //Backlog has a value of 5 i.e it can handle 5 connections
    clilen = sizeof(cli_addr);

    // Accept an incoming connection
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);     //returns a file descriptor
    if (newsockfd < 0) {
        perror("ERROR ON ACCEPT");
        exit(1);
    }
}

void receive_file(){
    int name_length;
    recv(newsockfd,&name_length,sizeof(name_length),0);
    char file_name[255];
    recv(newsockfd,file_name,name_length,0);
    file_name[name_length]='\0';

    long file_size;
    recv(newsockfd,&file_size,sizeof(file_size),0);

    FILE *file = fopen(file_name, "wb");
    if (file == NULL) {
        perror("ERROR OPENING FILE");
        return;
    }

    // Receive file data
    char buffer[1024];
    long bytes_received = 0;
    LONG n;
    while (bytes_received < file_size && (n = recv(newsockfd, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, n, file);
        bytes_received += n;
    }

    fclose(file);

}

void run_server() {
    int n;

    while (1) {
        memset(buffer, 0, 255);
        n = recv(newsockfd, buffer, 255, 0);
        if (n < 0) {
            perror("ERROR ON READING");
            exit(1);
        }
        printf("Client: %s", buffer);

        memset(buffer, 0, 255);
        fgets(buffer, 255, stdin);

        n = send(newsockfd, buffer, strlen(buffer), 0);
        if (n < 0) {
            perror("ERROR ON WRITING");
            exit(1);
        }

        if (strcmp("Bye\n", buffer) == 0) {
            break;
        }
    }

    close(newsockfd);
    close(sockfd);
}
