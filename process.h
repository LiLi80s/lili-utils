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

#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <iostream>
#include <pthread.h>
using namespace std;

#include "mutex.h"
#include "message_queue.h"
#include "message.h"

class Process{
private:
    pid_t mPid;
    char * mName;
    char * mDir;
    char ** mArgs;

public:
    Process():
    	mPid(0),mName(0),mDir(0),mArgs(0)
    {
    }
    Process(char* name, char* dir, char ** args):
        mPid(0),mName(name),mDir(dir),mArgs(args){
    }
    virtual ~Process(){}
    char* getName() {return mName;}
    pid_t getPid() {return mPid;}

public:
    
    int launch();

    int copy();

    int daemonize();

    virtual int wait();

    virtual int init();

};
#endif /*_PROCESS_H_*/
