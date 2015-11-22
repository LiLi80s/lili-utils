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

#ifndef _FOPS_H_
#define _FOPS_H_

#include <iostream>
#include <pthread.h>
using namespace std;

#include "mutex.h"
#include "message_queue.h"
#include "message.h"

class FileOperation{
public:
    typedef void (*FunctionOnExitPtr)(void*);

private:
    pthread_t mTid;
    char * mName;
    Mutex mMutex;
    MessageQueue *inQueue;
    MessageQueue *outQueue;
public:
    Actor(char* name, MessageQueue* in, MessageQueue* out):
        mTid(0),mName(name),
        inQueue(in),outQueue(out){}
    virtual ~Actor(){}
    char* getName() {return mName;}
    pthread_t getTid() {return mTid;}

private:
    static void* entry(void * arg0){
        Actor* actor = (Actor*) arg0;
        actor->run();
        return arg0;
    }

public:
    virtual void run()=0;
    
    int start(){
        int err;
        err = pthread_create(&mTid, NULL, entry, (void*)this); 
        if (err != 0)
            cout<<"can't create thread: " << strerror(err);
        return err;
    }

    int join(){
        void* tret = NULL;
        int err = pthread_join(mTid, &tret);
        if (err != 0){
            cout<<"can't join with thread 1: "<<strerror(err); 
        }else{
            cout<<"thread 1 exit code";
        }
        return err;
    }

    void stop(){
        pthread_exit((void *)mTid);
    }


};
#endif /*_FOPS_H_*/
