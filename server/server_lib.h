#ifndef MAIN_HEADERS_H
#define MAIN_HEADERS_H

#include<stdio.h>     //definitions of input and output
#include<stdlib.h>
#include<string.h>
// #include<unistd.h>

#ifdef _WIN32
    #include<winsock2.h>
    #include<ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include<unistd.h>
    #include<ctype.h>
    #include<sys/types.h>       //data types used in system calls
    #include<sys/socket.h>      //definitions of structures needed for socket
    #include<netinet/in.h>      //constants and structures needed for internet donain addresses
    #include<netdb.h>
#endif

void setup_server(int port);
void run_server();

#endif
