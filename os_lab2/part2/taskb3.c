#include <unistd.h>     
#include <fcntl.h>     
#include <stdlib.h>     
#include <sys/wait.h>   
#include <errno.h>      

#define BUFFER_SIZE 1024

void print_error(const char *msg) {
    write(STDERR_FILENO, msg, sizeof(char) * strlen(msg));
    write(STDERR_FILENO, "\n", 1);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        write(STDERR_FILENO, "Usage: ./task_b3 <file1> <file2> <file3>\n", 42);
        exit(1);
    }

   
    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 < 0) {
        write(STDERR_FILENO, "Error: Cannot open source file.\n", 32);
        exit(1);
    }

    int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd2 < 0) {
        write(STDERR_FILENO, "Error: Cannot open/create destination file2.\n", 46);
        close(fd1);
        exit(1);
    }

    int fd3 = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd3 < 0) {
        write(STDERR_FILENO, "Error: Cannot open/create destination file3.\n", 46);
        close(fd1);
        close(fd2);
        exit(1);
    }

   
    pid_t pid = fork();
    if (pid < 0) {
        write(STDERR_FILENO, "Error: fork() failed.\n", 23);
        close(fd1);
        close(fd2);
        close(fd3);
        exit(1);
    }

    if (pid == 0) {
        // ---------- CHILD PROCESS ----------
        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;

        
        lseek(fd1, 0, SEEK_SET);

        while ((bytes_read = read(fd1, buffer, BUFFER_SIZE)) > 0) {
            if (write(fd3, buffer, bytes_read) != bytes_read) {
                write(STDERR_FILENO, "Error writing to file3.\n", 24);
                close(fd1);
                close(fd2);
                close(fd3);
                exit(1);
            }
        }

        if (bytes_read < 0) {
            write(STDERR_FILENO, "Error reading from file1 in child.\n", 35);
        }

        close(fd1);
        close(fd2);
        close(fd3);

        exit(0);

    } else {
        // ---------- PARENT PROCESS ----------
        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;

       
        lseek(fd1, 0, SEEK_SET);

        while ((bytes_read = read(fd1, buffer, BUFFER_SIZE)) > 0) {
            if (write(fd2, buffer, bytes_read) != bytes_read) {
                write(STDERR_FILENO, "Error writing to file2.\n", 24);
                close(fd1);
                close(fd2);
                close(fd3);
                exit(1);
            }
        }

        if (bytes_read < 0) {
            write(STDERR_FILENO, "Error reading from file1 in parent.\n", 36);
        }

       
        wait(NULL);

        close(fd1);
        close(fd2);
        close(fd3);
    }

    return 0;
}
