#include <stdio.h>

void say_hello();
int add(int a, int b);

int main() {
    say_hello();
    printf("3 + 5 = %d\n", add(3, 5));
    return 0;
}
