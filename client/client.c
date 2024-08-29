#include "client_lib.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(1);
    }

    int portno = atoi(argv[2]);
    setup_client(argv[1], portno);
    run_client();

    return 0;
}