 #include<stdlib.h>
#include<stdio.h>
#include<time.h>
/* There is some amount of overlap with <sys/types.h> as known by inet code */
#ifndef __int8_t_defined
# define __int8_t_defined
typedef signed char        int8_t;
typedef short int          int16_t;
typedef int                int32_t;
# if __WORDSIZE == 64
typedef long int           int64_t;
# else
__extension__
typedef long long int      int64_t;
# endif
#endif

int main()
{
printf("Size of char: %d\n",sizeof(char));
printf("Size of short: %d\n",sizeof(short));
printf("Size of short int: %d\n",sizeof(short int));
printf("Size of int: %d\n",sizeof(int));
printf("Size of long int: %d\n",sizeof(long int));
printf("Size of unsigned int: %d\n",sizeof(unsigned int));
printf("Size of void *: %d\n",sizeof(void *));
printf("Size of size_t: %d\n",sizeof(size_t));
printf("Size of float: %d\n",sizeof(float));
printf("Size of double: %d\n",sizeof(double));
printf("Size of int8_t: %d\n",sizeof(int8_t));
printf("Size of int16_t: %d\n",sizeof(int16_t));
printf("Size of int64_t: %d\n",sizeof(int64_t));
printf("Size of time_t: %d\n",sizeof(time_t));
printf("Size of clock_t: %d\n",sizeof(clock_t));
printf("Size of struct tm: %d\n",sizeof(struct tm));
printf("Size of NULL: %d\n",sizeof(NULL));
return 0;
}



