
#include "client_lib.h"

static int sockfd;
static struct sockaddr_in serv_addr;
static struct hostent *server;

void setup_client(const char *hostname, int port) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR OPENING SOCKET");
        exit(1);
    }

    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr, "ERROR NO SUCH HOST\n");
        exit(1);
    }

    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR CONNECTING");
        exit(1);
    }
}

void send_file(const char *filename){
    FILE *fptr=fopen(filename,"r");
    if(fptr==NULL){
        perror("error in opening file");
        return ;
    }


    int words=0;
    char c;
    char buffer[255];
    while((c=getc(fptr))!=EOF){
        fscanf(fptr,"%s",buffer);
        if(isspace(c) || c=="\t"){
            words++;
        }
    }

    
    send(sockfd,&words,sizeof(int), 0);
    rewind(fptr);

    char ch ;
    while(ch!=EOF){
        fscanf(fptr,"%s",buffer);
        send(sockfd,buffer,255,0);
        ch=fgetc(fptr);
    }

    printf("the file has been successfully sent.THANKYOU");
}

void run_client() {
    char buffer[255];
    int n;

    while (1) {
        memset(buffer, 0, 255);
        fgets(buffer, 255, stdin);
        if(strncmp(buffer,"SEND_FILE ",10)==0){
            char*file_name=buffer+10;
            file_name[strcspn(file_name,"\n")]=0;
            send_file(file_name);
        }
        else{
            n = send(sockfd, buffer, strlen(buffer), 0);
            if (n < 0) {
                perror("ERROR ON WRITING");
                exit(1);
            }
        }
        

        memset(buffer, 0, 255);
        n = recv(sockfd, buffer, 255, 0);
        if (n < 0) {
            perror("ERROR ON READING");
            exit(1);
        }

        printf("server: %s", buffer);

        if (strcmp("Bye\n", buffer) == 0) {
            break;
        }
    }

    close(sockfd);
}
