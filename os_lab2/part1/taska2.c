#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc,char *argv[]) {
    char program[100]; // Buffer for program name

    while (1) {
        // Print prompt and read program name
        printf("Enter program: ");
        scanf("%s",program);
        pid_t p=fork();
        if(p<0){
            printf("fork failed\n");
            
        }
        else if(p==0){ 
            execvp(program,NULL);
        }
        else{
            int status;
            if(wait(&status)!=-1){
                printf("Child %d finished executing %s\n",p,program);
            }
        }
        
    }

    return 0;
}