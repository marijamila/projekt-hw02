#include <stdio.h>
#include <unistd.h>
#include "io.h"

int read_word(int fd) {
    void *buf;
    read(fd, buf, sizeof(int));
    return *(int *)buf;
}

short read_half(int fd) {
    void *buf;
    read(fd, buf, sizeof(short));
    return *(short *)buf;
}

void write_word(int fd, int word) {
    write(fd, &word, sizeof(int));
    return;
}

void write_half(int fd, short word) {
    write(fd, &word, sizeof(short));
    return;
}