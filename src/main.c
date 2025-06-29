
#include <stdio.h>
#include <stdlib.h>
#include "../include/server.h"

int main(int argc,char **argv) {
    
    handshake(argv[1],atoi(argv[2]));
    
    return 0;
}
