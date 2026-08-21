#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]){
    
    
    /*
    ToDo: Write your code here. Make changes as need be.
    */
    int n;
    scanf("%d",&n);  
    char name[n+1];
    read(0,name,n); 
    name[n]='\0';
  
    fprintf(stdout,"Hello %s !\n",name);

    write(1,"Logged in with the name ",25);
    write(1,name,strlen(name));
    write(1," !\n",3);

   
    return 0;
}