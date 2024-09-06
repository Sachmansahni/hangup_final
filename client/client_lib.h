#ifndef MAIN_HEADERS_H
#define MAIN_HEADERS_H

#include<stdio.h>
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
    #include<arpa/inet.h>
    #include<sys/types.h>
    #include<sys/socket.h>
    #include<netinet/in.h>
    #include<netdb.h>
#endif

#endif
