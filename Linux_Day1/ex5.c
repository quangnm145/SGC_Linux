#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

int main(void) {
    int fd;
    unsigned char data[3];

    fd = open("/dev/input/mice", O_RDONLY);
    if (fd == -1) {
        perror("Error opening /dev/input/mice");
        return 1;
    }

    while (1) {
        // Đọc dữ liệu chuột vào buffer
        if (read(fd, data, sizeof(data)) != sizeof(data)) {
            perror("Error reading data\n");
            close(fd);
            return 1;
        }

        signed char x_move = (signed char)data[1];
        signed char y_move = (signed char)data[2];

        printf("Mouse moved: x=%d, y=%d\n", x_move, y_move);
    }

    close(fd);
    return 0;
}
