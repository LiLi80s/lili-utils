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
    if (argc > 3){
        SocketActor* sa = new SocketActor(argv[1],argv[2],atoi(argv[3]),NULL,NULL);
        sa->start();
        sa->join();
    } 
    return 0;
}
