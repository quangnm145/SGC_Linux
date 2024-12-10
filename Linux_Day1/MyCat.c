// QuangNM41

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error arguments\n");
        return 1;
    }

    const char *filename = argv[1];
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("Error opening file");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    int err;
    while ((err = read(fd, buffer, sizeof(buffer))) > 0) {
        printf("%.*s", (int)err, buffer);
    }

    if (err == -1) {
        printf("Error reading file");
        return 1;
    }

    close(fd);
    return 0;
}

