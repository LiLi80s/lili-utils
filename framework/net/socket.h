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

#define MAX_CLIENT   1000
#define MAX_LENGTH   2000
#define MAX_PENDING  1000
/* Socket Listener for Monitoring the Specified Ip and Port. */
class SocketActor;
class SocketActorsList{
public:
    static map<char*, SocketActor* > mSocketActorsContainer; 
    static SocketActor* createSocketListener(char* name, char* ipAddr, short port, MessageQueue *in, MessageQueue *out);
};

class SocketActor : public Actor{
private:

    map<int, MessageQueue &> mMessageQueues;
    char* mIpAddr;
    char* mName;
    short mPort;
    fd_set mFDSet;
    int mListenerFD;
    int mMaxFD;
    int mClients[MAX_CLIENT];
    bool isListening(){return (mPort == -1) ? false:true;}
private:
    static SocketActorsList mSocketActors;

public:
    static SocketActorsList& sockets() {return mSocketActors;}

public:
    
    explicit SocketActor (char* name, char* ipAddr, short port,
               MessageQueue *in, MessageQueue *out);
    
    ~SocketActor ();
    char* getMyName(){
       return mName;
    }

    void run();

private:

    int initialize( void ); 

    int connect2( char* ipAddress, short port );

    int waiting( void );

    int incoming( void );

    int fork( void );

    int fork (int connfd);

private:

    char mDataBuffer[MAX_LENGTH];

    void queue( void );
};
#endif /*_SOCKET_CLI_H_*/
