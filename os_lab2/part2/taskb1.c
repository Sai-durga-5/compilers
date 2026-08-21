#include <unistd.h>     
#include <fcntl.h>      
#include <stdlib.h>    
#include <sys/wait.h>  
#include <string.h>     
#include <errno.h>   
#define BUFFER_SIZE 256


void print_error(const char *msg) {
    write(STDERR_FILENO, msg, strlen(msg));
    write(STDERR_FILENO, "\n", 1);
}

void write_fd(const char *label, int fd) {
    char buf[50];
    int len = 0;

    if (fd == 0) {
        buf[len++] = '0';
    } else {
        int temp = fd;
        char temp_buf[20];
        int i = 0;

        while (temp > 0) {
            temp_buf[i++] = '0' + (temp % 10);
            temp /= 10;
        }
        
        while (i > 0) {
            buf[len++] = temp_buf[--i];
        }
    }
    buf[len] = '\0';

 
    write(STDOUT_FILENO, label, strlen(label));
    write(STDOUT_FILENO, buf, strlen(buf));
    write(STDOUT_FILENO, "\n", 1);
}

int main() {
    
    int fd1 = open("test1.txt", O_RDONLY);
    if (fd1 < 0) {
        print_error("Error: Cannot open test1.txt");
        exit(1);
    }

    int fd2 = open("test2.txt", O_RDONLY);
    if (fd2 < 0) {
        print_error("Error: Cannot open test2.txt");
        close(fd1);
        exit(1);
    }

    write_fd("File descriptor for test1.txt: ", fd1);
    write_fd("File descriptor for test2.txt: ", fd2);

   
    if (close(fd1) < 0) {
        print_error("Error: Failed to close test1.txt");
        close(fd2);
        exit(1);
    }

    int fd3 = open("test3.txt", O_RDONLY);
    if (fd3 < 0) {
        print_error("Error: Cannot open test3.txt");
        close(fd2);
        exit(1);
    }

   
    write_fd("File descriptor for test3.txt: ", fd3);

   
    pid_t pid = fork();
    if (pid < 0) {
        print_error("Error: fork() failed");
        close(fd2);
        close(fd3);
        exit(1);
    }

    if (pid == 0) {
       
        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;

        bytes_read = read(fd2, buffer, BUFFER_SIZE - 1);
        if (bytes_read < 0) {
            print_error("Child: Error reading from test2.txt");
            close(fd2);
            close(fd3);
            exit(1);
        }

        buffer[bytes_read] = '\0';
        write(STDOUT_FILENO, "Child process read from test2.txt:\n", 35);
        write(STDOUT_FILENO, buffer, bytes_read);
        write(STDOUT_FILENO, "\n", 1);

        close(fd2);
        close(fd3);
        exit(0);
    } else {
        
        int status;
        if (wait(&status) < 0) {
            print_error("Error: wait() failed");
            close(fd2);
            close(fd3);
            exit(1);
        }

  
        write(STDOUT_FILENO, "Parent process: Child finished execution.\n", 42);

       
        close(fd2);
        close(fd3);
    }

    return 0;
}
