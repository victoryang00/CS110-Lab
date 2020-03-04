#include <stdio.h>
#include <assert.h>

#include "vector.h"

int main(int argc, const char* argv[]) {
    int i;

    printf("TESTING SETUP ...\n");
    Vector vector = {1,1,1,NULL};
    assert(!vector_is_initialized(&vector));
    vector_init(&vector, 0, sizeof(int));
    assert(vector_is_initialized(&vector));

    printf("TESTING INSERT ...\n");
    for (i = 0; i < 5; ++i) {
        assert(vector_insert(&vector, 0, &i) == VECTOR_SUCCESS);
        assert(VECTOR_GET_AS(int, &vector, 0) == i);
        assert(vector.size == i + 1);
    }

    int x = 5;
    vector_push_back(&vector, &x);
    vector_insert(&vector, vector.size, &x);

    printf("TESTING ASSIGNMENT ...\n");

    for (i = 0; i < vector.size; ++i) {
        int value = 666;
        vector_assign(&vector, i, &value);
        int *t= vector_get(&vector,i);
        printf("%d ",*t);
    }
    printf("\n-----------\n");
   bool less(int *a,int *b){
        return &a>&b;
    }
    vector_sort(&vector,less);
    for (i = 0; i < vector.size; ++i) {
        int *t= vector_get(&vector,i);
        printf("%d ",*t);
    }
    printf("\n");

    printf("TESTING ITERATION ...\n");



    printf("TESTING RESIZE ...\n");
    assert(vector_resize(&vector, 100) == VECTOR_SUCCESS);
    assert(vector.size == 100);
    assert(vector.capacity > 100);



    vector_destroy(&vector);

    printf("\033[92mALL TEST PASSED\033[0m\n");

    return 0;
}