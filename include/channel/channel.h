#ifndef CHANNEL_H
#define CHANNEL_H

#include <pthread.h>

#include "../buffer/ring_buffer.h"

// Opaque circular buffer structure
typedef struct channel_t channel_t;

// Handle type, the way users interact with the API
typedef channel_t * chan;

// The hidden definition of our circular buffer structure
struct channel_t {
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

/// Initializes the channel
channel_t * make(uint8_t* buffer, size_t size);

/// Writes to the channel
void write(channel_t ch, int value);

/// Reads from the channel
int read(channel_t ch);

#endif