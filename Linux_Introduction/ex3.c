//QuangNM41

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int fd;
    char proc_ID[10];
    char file_path[256];
    char buffer[100];
    int err;

    printf("Enter process ID: ");
    if (fgets(proc_ID, sizeof(proc_ID), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }

    /* The strcspn() function searches 
	for the first occurrence in a string of any of the specified characters 
	and returns the length of the string up to that point.*/
    proc_ID[strcspn(proc_ID, "\n")] = '\0';

    // Construct the file path
    snprintf(file_path, sizeof(file_path), "/proc/%s/comm", proc_ID);

	//folder /proc store running process. Each process has one ID, and it have 1 folder in /proc. 
	// Name of process is stored in comm file.
    fd = open(file_path, O_RDONLY);
    if (fd == -1) {
        printf("Error opening file");
        return 1;
    }

    // Read the process name from the file
    err = read(fd, buffer, sizeof(buffer) - 1);
    if (err == -1) {
        printf("Error reading file");
        close(fd);
        return 1;
    }
    buffer[err] = '\0';

    printf("Process name: %s\n", buffer);

    close(fd);
    return 0;
}
