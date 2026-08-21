#include <unistd.h>    
#include <fcntl.h>    
#include <stdlib.h>    
#include <errno.h>   
#include <string.h>    

#define BUFFER_SIZE 4096

void print_error(const char *msg) {
    write(STDERR_FILENO, msg, strlen(msg));
    write(STDERR_FILENO, "\n", 1);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        print_error("Usage: ./task_b2 <file1> <file2> <file3> <offset>");
        exit(1);
    }

    int offset = atoi(argv[4]);
    if (offset < 0) {
        print_error("Error: Offset must be a non-negative integer.");
        exit(1);
    }

    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 < 0) {
        print_error("Error: Cannot open file1.");
        exit(1);
    }

    int fd2 = open(argv[2], O_RDONLY);
    if (fd2 < 0) {
        print_error("Error: Cannot open file2.");
        close(fd1);
        exit(1);
    }

    int fd3 = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd3 < 0) {
        print_error("Error: Cannot open/create file3.");
        close(fd1);
        close(fd2);
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    
    while ((bytes_read = read(fd2, buffer, BUFFER_SIZE)) > 0) {
        ssize_t bytes_written = write(fd3, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            print_error("Error: Writing to file3 failed while copying file2.");
            close(fd1);
            close(fd2);
            close(fd3);
            exit(1);
        }
    }
    if (bytes_read < 0) {
        print_error("Error: Reading from file2 failed.");
        close(fd1);
        close(fd2);
        close(fd3);
        exit(1);
    }

    if (lseek(fd3, offset, SEEK_SET) < 0) {
        print_error("Error: lseek() failed.");
        close(fd1);
        close(fd2);
        close(fd3);
        exit(1);
    }

    while ((bytes_read = read(fd1, buffer, BUFFER_SIZE)) > 0) {
        ssize_t bytes_written = write(fd3, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            print_error("Error: Writing to file3 failed while copying file1.");
            close(fd1);
            close(fd2);
            close(fd3);
            exit(1);
        }
    }
    if (bytes_read < 0) {
        print_error("Error: Reading from file1 failed.");
        close(fd1);
        close(fd2);
        close(fd3);
        exit(1);
    }

 
    close(fd1);
    close(fd2);
    close(fd3);

    return 0;
}
