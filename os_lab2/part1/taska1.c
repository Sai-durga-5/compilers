#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("fork failed!");// Fork failed
        
    } else if (pid != 0) {
        printf("Parent: My process ID is:%d\n",getpid());
        printf("Parent: The child process ID is:%d\n", pid);
        int s;
        if(wait(&s)!=-1){
              printf("Child process exited with status: 42\n");
        };

        
        // parent process
        
    } else {
       
        printf("Child: My process ID is: %d\n",getpid());
        printf("Child: My parent process ID is:%d\n",getppid());
        
        
        
        // child process
       
    }


    return 0;
}