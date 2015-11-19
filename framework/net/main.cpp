#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "message.h"
#include "message_queue.h"
#include "mutex.h"
#include "actor.h"
#include "socket.h"

int main( int argc, char** argv ){
    
    int nbrOfArgs = argc;
    if (argc == 4){
        SocketActor* sa = new SocketActor(argv[1],argv[2],atoi(argv[3]),NULL,NULL);
        sa->start();
        sa->join();
    }
    if (argc == 5){
        SocketActor* sa = new SocketActor(argv[1],argv[2],(short)(-1),NULL,NULL);
        sa->connect2(argv[2],atoi(argv[3]));
        sa->start();
        sa->join();
    }
    return 0;
}
