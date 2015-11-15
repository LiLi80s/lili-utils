#ifndef _MESSAGE_QUEUE_H_
#define _MESSAGE_QUEUE_H_

#include <iostream>
#include <vector>


#include "Mutex.h"
#include "Message.h"

using namespace std;

class MessageQueue{
private:
    vector<Message*> mQueue;

public:
    void push(Message* message){
        Mutex mutex;
        mQueue.push_back(message);
    }
    Message* pop(Message* message){
        Mutex mutex;
        return mQueue.front();
    }

};

#endif /*_MESSAGE_QUEUE_H_*/
