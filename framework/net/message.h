#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#define PROTO_LENGTH 1000


class Message{
private:
    char mPayload[PROTO_LENGTH];
public:
    char* getBuffer( void ) {return &(mPayload[0]);}
    virtual void processMessage( void ){}
};


#endif /*_MESSAGE_H_*/
