
#include "server_lib.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(1);
    }

    int portno = atoi(argv[1]);
    setup_server(portno);
    run_server();

    return 0;
}
