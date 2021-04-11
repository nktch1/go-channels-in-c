#include "include/channel/channel.h"

int main() {
    chan testCh = make(sizeof(int), 8);

    int value = 1126;
    send(testCh, (void*)value);


    return 0;
}