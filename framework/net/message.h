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
#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <stdlib.h>
#include <unistd.h>
#include <memory.h>

#include "proto.h"

#define PROTO_LENGTH 1000

class Message{
private:
    char *mPayload;
    DataHandler* mDher;
public:

    Message(int len){
        mPayload = (char*) malloc(len);
    }
    ~Message () {
        if (mPayload) 
            free(mPayload);
        mPayload = NULL; 
    }
    char* getBuffer( void ) {return mPayload;}
    virtual void process( void ){mDher->process(mPayload);}
};

#endif /*_MESSAGE_H_*/
