
#include "Mutex.h"
#include "Message.h"


class MessageQueue{
private:
    vector<Message*> mQueue;

public:
    int push(Message* message){
        Mutex mutex;
        mQueue.push_back(message);
    }
    Message* pop(Message* message){
        Mutex mutex;
        return mQueue.front();
    }

};
