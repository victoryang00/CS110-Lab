//#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define mag(a,b) (sqrt(a*a+b*b))
int main(){
int a=3;
float b=mag(++a,4);
int c=b*b;
printf("%d",c);
return 0;}
