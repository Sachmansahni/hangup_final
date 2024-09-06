Overview
--------
This project is a command-line-based chat server and client system implemented in C, using socket programming to enable real-time text communication over a TCP/IP connection. The client can connect to the server on a specified port, and the two systems can exchange messages.


The project highlights key concepts in socket programming such as:
-----------------------------------------------------------------
Socket creation
Binding
Listening for incoming connections
Accepting and handling connections
Data transmission and reception (text messages)


Features
--------
Real-time Text Messaging: Enables exchange of text messages between a client and a server.
Cross-Platform Support: Works on both Windows and Linux-based systems (platform-specific headers included).


Setup
Prerequisites
-------------
C Compiler: You need a C compiler like GCC (on Linux) or MinGW (on Windows).
Network Access: Ensure both the client and server machines are connected over the network.


Windows Specifics
-----------------
Ensure that winsock2.h and ws2tcpip.h libraries are linked when compiling on Windows.
For MinGW users, the command to compile may look like:

gcc -o client client.c -lws2_32
gcc -o server server.c -lws2_32


Linux Specifics
---------------
The standard socket libraries (sys/socket.h, arpa/inet.h) are used.
You can compile using:

gcc -o client client.c
gcc -o server server.c


How It Works
------------

1. Client

The client program establishes a connection with the server and sends text messages:

Connection Setup:
The client uses gethostbyname() to resolve the hostname and connect() to establish a TCP connection.

Message Exchange:
The client can send text messages directly to the server. The server processes and responds to the messages.



2. Server

The server listens on a specified port for incoming client connections:

Connection Setup:
It uses bind() to bind the socket to an IP address and port, and accept() to handle incoming connections.

Message Exchange:
The server can send responses back to the client.


Code Structure
--------------
Header File (main_headers.h)
Contains platform-specific includes for both Windows (winsock2.h, ws2tcpip.h) and Linux (arpa/inet.h, sys/socket.h).
Manages cross-platform compatibility with #ifdef _WIN32.


Client Implementation
---------------------
setup_client(): Establishes a connection to the server.
run_client(): Main loop for sending messages to the server and receiving responses.
Server Implementation
setup_server(): Prepares the server for incoming connections.
run_server(): Main loop for receiving messages from the client and sending responses back.