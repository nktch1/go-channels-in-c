#include "../../include/channel/channel.h"

chan make(size_t type_size, size_t size) {
    struct chan* ch = malloc(sizeof(struct chan));

    pthread_mutex_init(&ch->lock, NULL);

    ch->buf = circular_buf_init(
            malloc(size * type_size), size);

    ch->elemsize = type_size;
    ch->qcount = 0;
    ch->closed = 0;
    ch->dataqsiz = 0;
    ch->recvx = 0;
    ch->sendx = 0;

    return ch;
}

void send(chan ch, void* value) {

}

void* receive(chan ch) {

}

void close(chan ch) {

}