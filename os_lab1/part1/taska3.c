#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char *argv[]){
    
    
    /*
    ToDo: Write your code here. Make changes as need be.
    */
    double a1,a2,a3,a4,a5;
    scanf("%lf", &a1);
    scanf("%lf", &a2);
    scanf("%lf", &a3);
    scanf("%lf", &a4);
    scanf("%lf", &a5);
    float b1,b2,b3,b4,b5;
    b1=(int)(sin(1/(1+exp(-a1)))*1000)/1000.0;
    b2=(int)(sin(1/(1+exp(-a2)))*1000)/1000.0;
    b3=(int)(sin(1/(1+exp(-a3)))*1000)/1000.0;
    b4=(int)(sin(1/(1+exp(-a4)))*1000)/1000.0;
    b5=(int)(sin(1/(1+exp(-a5)))*1000)/1000.0;
    printf("%0.3f\n", b1);
    printf("%0.3f\n", b2);
    printf("%0.3f\n", b3);
    printf("%0.3f\n", b4);
    printf("%0.3f\n", b5);

 
    return 0;
}