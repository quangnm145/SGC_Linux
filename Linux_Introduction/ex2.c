//QuangNM41

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    int fd;
    int err;
    const char *file_path = "./src/ex2.txt";
    char buffer[1024];

    fd = open(file_path, O_CREAT | O_RDWR | O_TRUNC);
    if (fd == -1) {
        printf("Error opening file");
        return 1;
    }

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    
    err = write(fd, buffer, strlen(buffer));
    if (err == -1) {
        printf("Error writing to file");
        close(fd);
        return 1;
    }
    memset(buffer, 1024, '\0');

    err = lseek(fd, 0, SEEK_SET);
    if (err == -1) {
        printf("Error seeking file");
        close(fd);
        return 1;
    }

    err = read(fd, buffer, sizeof(buffer) - 1);
    if (err == -1) {
        printf("Error reading file");
        close(fd);
        return 1;
    }
    buffer[err] = '\0';

    printf("Content of the file: %s\n", buffer);

    close(fd);
    return 0;
}
