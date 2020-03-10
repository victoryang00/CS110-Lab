#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#define sz(type) printf("Size of %s: %d\n", #type, (int)sizeof(type));
int main() {
    sz(char);
    sz(short);
    sz(short int);
    sz(int);
    sz(long int);
    sz(unsigned int);
    sz(void *);
    sz(size_t);
    sz(float);
    sz(double);
    sz(int8_t);
    sz(int16_t);
    sz(int32_t);
    sz(int64_t);
    sz(time_t);
    sz(clock_t);
    sz(struct tm);
    sz(NULL);
    return 0;
}
