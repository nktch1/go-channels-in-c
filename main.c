#include "include/buffer/ring_buffer.h"
#include "include/channel/channel.h"

const int EXAMPLE_BUFFER_SIZE = 10;

int main() {
    uint8_t* buffer = malloc(EXAMPLE_BUFFER_SIZE * sizeof(uint8_t));
    chan chan1 = make(buffer, EXAMPLE_BUFFER_SIZE);

    free(buffer);

    return 0;
}
