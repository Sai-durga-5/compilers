#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        return 0;// Fork failed
        
    } else if (pid == 0) {
         printf("Child (PID: %d): Parent PID is %d\n",getpid(),getppid());// Child process
         sleep(8);
         printf("Child (PID: %d): I am now an orphan, new Parent PID is %d\n",getpid(),getppid());
         
         
    } else {
       printf("Parent (PID: %d): Child PID is %d\n",getpid(),pid); // Parent process
        // Parent exits immediately to make child an orphan
        
    }

    return 0;
}