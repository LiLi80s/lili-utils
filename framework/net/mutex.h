

#ifndef _MUTEX_H_
#define _MUTEX_H_

#include <iostream>
#include <pthread.h>


class Mutex{
public:
    Mutex(){
        pthread_mutex_init(&m,NULL);
    }

    ~Mutex(){
        pthread_mutex_destroy(&m);
    }
    void lock(){
        pthread_mutex_lock(&m);
    }

    void unlock(){
        pthread_mutex_unlock(&m);
    }
    
private:
    pthread_mutex_t m;
};


#endif /*_MUTEX_H_*/
