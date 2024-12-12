#include <stdio.h>

void say_hello() {
    printf("Hello from shared library!\n");
}

int add(int a, int b) {
    return a + b;
}
