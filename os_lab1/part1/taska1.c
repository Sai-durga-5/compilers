#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    
    
    /*
    ToDo: Write your code here. Make changes as need be.
    */
    printf("Hello World!\n"); 
    char name[30];   
    fgets(name,30,stdin);  
    name[strlen(name)-1]='\0';     
    printf("Hello %s %d ",name,strlen(name));

    return 0;
}