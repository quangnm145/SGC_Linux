#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[])
{
    int input_fd, output_fd;
    long numRead;
    char buf[BUF_SIZE], c;
 
    if (argc != 3) {
        printf("Error argument: %s <source_file> <dest_file>\n", "MyCp");
        return 1;
    }

    input_fd = open(argv[1], O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (input_fd == -1) {
        printf("opening file %s %d", argv[1], 1);
        return 1;
    }

    output_fd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (output_fd == -1)
        printf("opening file %s %d", argv[2], 2);
 
    int holes = 0;
    while ((numRead = read(input_fd, buf, BUF_SIZE)) > 0) 
    {
        for (int i = 0; i < numRead; i++) {
            if (buf[i] == '\0') {
                holes++;
                continue;
            } else if (holes > 0) {
                lseek(output_fd, holes, SEEK_CUR);
                holes = 0;
            }
            if (write(output_fd, &buf[i], 1) != 1) {
                printf("Error write char to file");
                return 1;
            }
        }
    }
 
    close(output_fd);
    close(input_fd);
    return 0;
}