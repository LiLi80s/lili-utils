/*************************************************************************
* Copyright Liqun LIU [liulq80s@gmail.com]
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*     http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
***************************************************************************/



#include <iostream>
//#include <netinet/net.h>
#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>

#include "actor.h"
#include "message.h"
#include "message_queue.h"
#include "mutex.h"
#include "socket.h"

using namespace std;



#define MAX_CLIENT   1000
#define MAX_LENGTH   2000
#define MAX_PENDING  1000
/* Socket Listener for Monitoring the Specified Ip and Port. */

    
SocketActor::SocketActor (char* name, char* ipAddr, short port,
           MessageQueue *in, MessageQueue *out):
    Actor(name,in,out),
    mName(name), mIpAddr(ipAddr), mPort(port)
{
    mListenerFD = initialize();
    FD_ZERO(&mFDSet);
    FD_SET(mListenerFD, &mFDSet);
    for (int i = 0; i < MAX_CLIENT; i++)
        mClients[i] = -1;                 /* -1 indicates available entry */
}

SocketActor::~SocketActor (){
}

void SocketActor::run()
{
    while(1){
        int nbr = waiting();
        if ( nbr > 0 ){
            if (incoming())
                fork();
            queue();
        }
    }
}

int SocketActor::initialize( void ) 
{
    if (isListening()){
        int  listenfd;
        struct sockaddr_in servaddr;
        listenfd = socket(AF_INET, SOCK_STREAM, 0); 
        bzero(&servaddr, sizeof(servaddr));
        {
            servaddr.sin_family      = AF_INET;
            inet_pton(AF_INET, mIpAddr, &(servaddr.sin_addr));
            servaddr.sin_port        = htons(mPort);
        }
        bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
        listen(listenfd, MAX_PENDING  );
        return listenfd;
    }
    else
        return -1;
}

int SocketActor::connect2( char* ipAddress, short port ){
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress, &servaddr.sin_addr);

    if (0 != connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))){
        return -1;
    }

    //new SocketConnection
    return fork(sockfd);
}

int SocketActor::waiting( void )
{
    return select(mMaxFD+1, &mFDSet, NULL, NULL, NULL);
}

int SocketActor::incoming( void )
{
    if (isListening())
        return FD_ISSET(mListenerFD, &mFDSet);
    else
        return false;
}

int SocketActor::fork( void )
{
    socklen_t clilen = (socklen_t)sizeof(sockaddr);
    struct sockaddr_in cliaddr;
    int connfd = accept(mListenerFD, (struct sockaddr *)(&cliaddr), &clilen);
    return fork (connfd);
}

int SocketActor::fork (int connfd){
    int i = 0;
    for (; i < MAX_CLIENT; i++){
        if (mClients[i] == -1) {
            mClients[i] = connfd;     /* save descriptor */
            break;
        }
    }

    if (i == MAX_CLIENT){
        std::cout<<"too many clients"<<std::endl;
        return -1;
    }

    FD_SET(connfd, &mFDSet);        /* add new descriptor to set */
    if (connfd > mMaxFD)
        mMaxFD = connfd;                 /* for select */

    return 0;
    
}

void SocketActor::queue( void )
{
    int sockfd = 0;
    for (int i = 0; i <= MAX_CLIENT; i++) {   /* check all clients for data */
        if ( (sockfd = mClients[i]) < 0)
           continue;
        if (FD_ISSET(sockfd, &mFDSet)) {
            int nbrOfBytes = 0;
            if ( (nbrOfBytes = read(sockfd, mDataBuffer, MAX_LENGTH)) == 0) {
                close(sockfd);
                FD_CLR(sockfd, &mFDSet);
                mClients[i] = -1;
                //Close Threads and Delete Related Services
            } else{
                // Parse the Package.
            }
        }  
    }
}


map<char*, SocketActor* > SocketActorsList::mSocketActorsContainer; 
SocketActor* SocketActorsList::createSocketListener(char* name, char* ipAddr, short port, MessageQueue *in, MessageQueue *out){
    map<char*, SocketActor* >::iterator itor = mSocketActorsContainer.find(name);
    if (itor != mSocketActorsContainer.end()) 
        return (SocketActor*)0;
    
    SocketActor* sa = new SocketActor(name,ipAddr,port,in,out);
    mSocketActorsContainer.insert(std::make_pair(name,sa));
    
    return sa;
}
