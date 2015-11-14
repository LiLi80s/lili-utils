
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

#ifndef _SOCKET_H_
#define _SOCKET_H_


#include <iostream>
#include <netinet/net.h>
#include <map>
#include <stdlib.h>
#include <stdio.h>

#include "Actor.h"


#define MAX_CLIENT = 1000;
#define MAX_LENGTH = 2000;

/* Socket Listener for Monitoring the Specified Ip and Port. */

class SocketListener : public Actor{
private:

    map<int, MessageQueue &> mMessageQueues;
    const char* mIpAddr;
    const char* mName;
    unsigned short mPort;
    fd_set mFDSet;
    int mListenerFD;
    int mClients[MAX_CLIENT];

private:

    static class SocketContainer{
        static map<const char*, SocketListener* > mSocketListeners; 
        static SocketListener* createSocketListener(const char* name, const char* ipAddr, unsigned short port)
        {
            map<const char*, SocketListener* >::iterator itor = mSocketListeners.find(name);
            if (itor != mSocketListeners.end()) 
                return (SocketListener*)0;
            
            SocketListener* sl = new SocketListener(name,ipAddr,port);
            mSocketListeners.insert(std::make_pair(name,sl));
            
            return sl;
        }
    }mSocketContainer;

public:

    static SocketContainer& sockets() {return mSocketContainer;}

public:

    SocketListener(const char* name,
        const char * ipAddr, unsigned short port):
        mName(name),mMessageQueue(messageQueue),
        mIpAddr(ipAddr),mPort(port)
    {
        mListenerFD = initialize();
        FD_ZERO(&mFDSet);
        FD_SET(mListenFD, &mFDSet);
        for (i = 0; i < FD_SETSIZE; i++)
            mClients[i] = -1;                 /* -1 indicates available entry */
    }

    char* getMyName(){
       return mName;
    }

    void run()
    {
        while(1){
            int nbr = select();
            if ( nbr > 0 ){
                if (incoming())
                    fork();
                queue();
            }
        }
    }

private:

    int initialize( void ) 
    {
        int  listenfd;
        struct sockaddr_in servaddr;
        listenfd = socket(AF_INET, SOCK_STREAM, 0); 
        bzero(&servaddr, sizeof(servaddr));
        {
            servaddr.sin_family      = AF_INET;
            htonl(inet_pton(AF_INET, mIpAddr, &(servaddr.sin_addr)));
            servaddr.sin_port        = htons(mPort);
        }
        bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
        listen(listenfd, LISTENQ);
        return listenfd;
    }

    int select( void )
    {
        return select(mMaxFD+1, &mFDSet, NULL, NULL, NULL);
    }

    int incoming( void )
    {
        return FD_ISSET(mListenerFD, &mFDSet);
    }

    int fork( void )
    {
        int clilen = sizeof(cliaddr);
        int connfd = accept(listenfd, (SA *) &cliaddr, &clilen);

        for (i = 0; i < FD_SETSIZE; i++){
            if (mClient[i] == -1) {
                mClient[i] = connfd;     /* save descriptor */
                break;
            }
        }

        if (i == FD_SETSIZE){
            std::cout<<"too many clients"<<std::endl;
            return -1;
        }

        FD_SET(connfd, &mFDSet);        /* add new descriptor to set */
        if (connfd > mMaxFD)
            mMaxFD = connfd;                 /* for select */

        return 0;
    }
private:

    char mDataBuffer[MAX_LENGTH] = {0};

    void queue( void )
    {
        int sockfd = 0;
        for (i = 0; i <= MAX_CLIENT; i++) {   /* check all clients for data */
            if ( (sockfd = mClient[i]) < 0)
               continue;
            if (FD_ISSET(sockfd, &mFDSet)) {
                if ( (n = read(sockfd, mDataBuffer, MAX_LENGTH)) == 0) {
                    close(sockfd);
                    FD_CLR(sockfd, &mFDSet);
                    mClient[i] = -1;
                    //Close Threads and Delete Related Services
                } else{
                    // Parse the Package.
                }
            }  
        }
    }
};
#endif /*_SOCKET_H_*/
