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

#ifndef _SIG_HANDLER_H_
#define _SIG_HANDLER_H_

#include <iostream>
#include <pthread.h>
using namespace std;

#include "mutex.h"
#include "message_queue.h"
#include "message.h"

class SignalHandler{

private:

    pid_t mOwnerPid;
    char *mOwnerName;
public:

    SignalHandler(pid_t pid, char* name):mOwnerPid(pid),mOwnerName(name){}
    virtual ~SignalHandler(){}
    char* getProcessName() {return mOwnerName;}
    pid_t getProcessPid() {return mOwnerPid;}
    virtual int handle() = 0;
};

class SignalManager{

private:
    
    map<int , SignalHandler *> mHandlers; 
    pid_t mOwnerPid;
    char *mOwnerName;
    SignalHandler* signalBuilder(pid_t pid, char* name, );
public:
    SignalManager(pid_t pid, char* name, int *sigs):
          mOwnerPid(pid),mOwnerName(name){}
    virtual ~SignalManager(){}

};



#endif /*_SIG_HANDLER_H_*/
