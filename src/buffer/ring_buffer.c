#include "../../include/buffer/ring_buffer.h"

// Moves the pointer forward (private)
static void advance_pointer(cbuf_handle_t cbuf);

// Moves the pointer backward (private)
static void retreat_pointer(cbuf_handle_t cbuf);

cbuf_handle_t circular_buf_init(uint8_t* buffer, size_t size) {
    assert(buffer && size);

    cbuf_handle_t cbuf = malloc(sizeof(circular_buf_t));
    assert(cbuf);

    cbuf->buffer = buffer;
    cbuf->max = size;
    circular_buf_reset(cbuf);

    assert(circular_buf_empty(cbuf));

    return cbuf;
}

void circular_buf_reset(cbuf_handle_t cbuf) {
    assert(cbuf);

    cbuf->head = 0;
    cbuf->tail = 0;
    cbuf->full = false;
}

void circular_buf_free(cbuf_handle_t cbuf) {
    assert(cbuf);

    free(cbuf);
}

bool circular_buf_full(cbuf_handle_t cbuf) {
    assert(cbuf);

    return cbuf->full;
}

bool circular_buf_empty(cbuf_handle_t cbuf) {
    assert(cbuf);

    return (!cbuf->full && (cbuf->head == cbuf->tail));
}

size_t circular_buf_capacity(cbuf_handle_t cbuf) {
    assert(cbuf);

    return cbuf->max;
}

size_t circular_buf_size(cbuf_handle_t cbuf) {
    assert(cbuf);

    size_t size = cbuf->max;

    if (cbuf->full) {
        return size;
    }

    size = cbuf->max + cbuf->head - cbuf->tail;

    if (cbuf->head >= cbuf->tail) {
        size = cbuf->head - cbuf->tail;
    }

    return size;
}

void circular_buf_put(cbuf_handle_t cbuf, uint8_t data) {
    assert(cbuf && cbuf->buffer);

    cbuf->buffer[cbuf->head] = data;

    advance_pointer(cbuf);
}

int circular_buf_get(cbuf_handle_t cbuf, uint8_t *data) {
    assert(cbuf && data && cbuf->buffer);

    int r = -1;

    if(!circular_buf_empty(cbuf)) {
        *data = cbuf->buffer[cbuf->tail];
        retreat_pointer(cbuf);

        r = 0;
    }

    return r;
}

static void advance_pointer(cbuf_handle_t cbuf) {
    assert(cbuf);

    if (cbuf->full && (++(cbuf->tail) == cbuf->max)) {
        cbuf->tail = 0;
    }

    if (++(cbuf->head) == cbuf->max) {
        cbuf->head = 0;
    }

    cbuf->full = (cbuf->head == cbuf->tail);
}

static void retreat_pointer(cbuf_handle_t cbuf) {
    assert(cbuf);

    cbuf->full = false;

    if (++(cbuf->tail) == cbuf->max) {
        cbuf->tail = 0;
    }
}



