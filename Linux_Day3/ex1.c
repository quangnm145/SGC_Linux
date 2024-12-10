#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 4096

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source file> <destination file>\n", argv[0]);
        return 1;
    }

    // Open source file for reading
    int src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening source file");
        return 1;
    }

    // Open or create destination file for writing
    int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("Error opening destination file");
        close(src_fd);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    ssize_t bytes_written;
    off_t current_offset = 0;

    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        size_t hole_start = 0;
        size_t i;

        for (i = 0; i < bytes_read; ++i) {
            if (buffer[i] == '\0') {
                // Start of a hole
                if (hole_start == (size_t)-1) {
                    hole_start = i;
                }
            } else {
                // End of a hole, write non-hole data
                if (hole_start != (size_t)-1) {
                    // Skip the hole in the destination file
                    current_offset += i - hole_start;
                    if (lseek(dest_fd, current_offset, SEEK_SET) == (off_t)-1) {
                        perror("Error seeking in destination file");
                        close(src_fd);
                        close(dest_fd);
                        return 1;
                    }
                    hole_start = (size_t)-1;
                }
                // Write the non-null byte
                if (write(dest_fd, &buffer[i], 1) != 1) {
                    perror("Error writing to destination file");
                    close(src_fd);
                    close(dest_fd);
                    return 1;
                }
                current_offset++;
            }
        }

        // Handle remaining hole at the end of the buffer
        if (hole_start != (size_t)-1) {
            current_offset += bytes_read - hole_start;
            if (lseek(dest_fd, current_offset, SEEK_SET) == (off_t)-1) {
                perror("Error seeking in destination file");
                close(src_fd);
                close(dest_fd);
                return 1;
            }
        }
    }

    if (bytes_read == -1) {
        perror("Error reading source file");
    }

    close(src_fd);
    close(dest_fd);

    return 0;
}
