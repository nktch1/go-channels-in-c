#ifndef CHANNEL_H
#define CHANNEL_H

#include <pthread.h>
#include "../buffer/ring_buffer.h"

typedef struct channel_t channel_t;
typedef channel_t* chan;

struct chan {
    cbuf_handle_t buf;     // points to an array of dataqsiz elements

    u_int32_t qcount;      // total data in the queue
    u_int32_t dataqsiz;    // size of the circular queue
    u_int16_t elemsize;
    u_int32_t closed;
    u_int32_t sendx;     // send index
    u_int32_t recvx;     // receive index

//    recvq    waitq  // list of recv waiters
//    sendq    waitq  // list of send waiters

    pthread_mutex_t lock;
};

///// Initializes the channel
chan make(size_t type_size, size_t size);

///// Sends to the channel
void send(chan ch, void* value);

///// Receives from the channel
void* receive(chan ch);

///// Closes the channel
void close(chan ch);

#endif