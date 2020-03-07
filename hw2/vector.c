#include "vector.h"
#include <stdlib.h>
#include <string.h>

/* define PRIVATE func. */
int vector_align(Vector *vector, size_t new_capacity);

int vector_init(Vector *vector, size_t capacity, size_t element_size)
{
    /* check whether vector is NULL. */
    if (vector == NULL)
        return VECTOR_ERROR;
    /* initializer. */
    vector->size = 0;
    vector->capacity = MAX(VECTOR_MINIMUM_CAPACITY, capacity);
    vector->element_size = element_size;
    vector->data = malloc(vector->capacity * element_size);
    /* return. */
    return vector->data == NULL ? VECTOR_ERROR : VECTOR_SUCCESS;
}

int vector_copy(Vector *destination, Vector *source)
{
    /* check whether vector is NULL. */
    if (destination == NULL || source == NULL || destination->data != NULL ||
        !(source->data != NULL))
        return VECTOR_ERROR;

    /* Copy size the size data */
    destination->size = source->size;
    destination->capacity = source->capacity;
    /* Copy size the element. */
    destination->element_size = source->element_size;

    /* malloc. */
    destination->data = malloc(destination->capacity * source->element_size);
    if (destination->data == NULL)
        return VECTOR_ERROR;
    /* memcpy. */
    memcpy(destination->data, source->data,
           source->element_size * source->size);

    return VECTOR_SUCCESS;
}

/* Insertion */
int vector_push_back(Vector *vector, void *element)
{
	/* define index. */
    int index;
    void *offset;
	if(vector == NULL||element==NULL)return VECTOR_ERROR;
    /* check whether vector is NULL. */
    if (vector->size == vector->capacity &&
        vector_align(vector, MAX(1, vector->size * VECTOR_GROWTH_FACTOR)) ==
            VECTOR_ERROR)
        return VECTOR_ERROR;

    /* get index. */
    index = vector->size;
    offset = (char *)vector->data + (index * vector->element_size);
    /* memcpy. */
    memcpy(offset, element, vector->element_size);
    ++vector->size;

    /* return. */
    return VECTOR_SUCCESS;
}

int vector_push_front(Vector *vector, void *element)
{

	/*check nullable*/
	if (vector == NULL)
        return VECTOR_ERROR;
    /* return. */
    return vector_insert(vector, 0, element);
}

int vector_insert(Vector *vector, size_t index, void *element)
{
    void *offset;
    size_t elements_bit;
    /* check whether vector is NULL. */
    if (vector == NULL || element == NULL || vector->element_size == 0 ||
        index > vector->size)
        return VECTOR_ERROR;
    /* check whether vector has capacity probs. */
    if ((vector->size == vector->capacity &&
         vector_align(vector, MAX(1, vector->size * VECTOR_GROWTH_FACTOR)) ==
             VECTOR_ERROR))
        return VECTOR_ERROR;

    /* move right. */
    offset = (char *)vector->data + (index * vector->element_size);
    elements_bit = (vector->size - index) * vector->element_size;
    memmove((char *)offset + vector->element_size, offset, elements_bit);

    /* insert the element */
    offset = (char *)vector->data + (index * vector->element_size);
    memcpy(offset, element, vector->element_size);
    ++vector->size;
    /* return */
    return VECTOR_SUCCESS;
}

int vector_assign(Vector *vector, size_t index, void *element)
{
    void *offset;
    /* check whether vector is NULL. */
    if (vector == NULL || element == NULL || vector->element_size == 0 ||
        index >= vector->size)
        return VECTOR_ERROR;
    /* update the offset */
    offset = (char *)vector->data + (index * vector->element_size);
    memcpy(offset, element, vector->element_size);

    return VECTOR_SUCCESS;
}

/* Deletion */
int vector_pop_back(Vector *vector)
{
    /* check whether vector is NULL. */
    if (vector == NULL || vector->element_size == 0)
        return VECTOR_ERROR;

    --vector->size;
    /* delete. */
    if (vector->size == vector->capacity * VECTOR_MINIMUM_CAPACITY)
        vector_align(vector, MAX(1, vector->size * VECTOR_GROWTH_FACTOR));

    return VECTOR_SUCCESS;
}

int vector_pop_front(Vector *vector)
{ 
	/*check nullable*/
	if (vector == NULL)
        return VECTOR_ERROR;
	/* pop front==erase. */
    return vector_erase(vector, 0);
}

int vector_erase(Vector *vector, size_t index)
{
    /* define right and offset */
    size_t right;
    void *offset;
    /* check whether vector is NULL. */
    if (vector == NULL || vector->element_size == 0 || index >= vector->size)
        return VECTOR_ERROR;
    /* update the offset */
    offset = (char *)vector->data + (index * vector->element_size);
    right = (vector->size - index - 1) * vector->element_size;

    /* move. */
    memmove(offset, (char *)offset + vector->element_size, right);

    /* check whether vector is devided by 4. */
    if (--vector->size == vector->capacity / 4) {
        vector_align(vector, MAX(1, vector->size * VECTOR_GROWTH_FACTOR));
    }

    return VECTOR_SUCCESS;
}

int vector_clear(Vector *vector) {
	/* check nullable  */
	if (vector == NULL)
        return VECTOR_ERROR;
	/* return size */
	return vector_resize(vector, 0); }

/* Lookup */
void *vector_get(Vector *vector, size_t index)
{
    /* check valibility */
    if (vector == NULL || vector->element_size == 0 || index >= vector->size)
        return NULL;
    /* return */
    return (char *)vector->data + (index * vector->element_size);
}

void *vector_front(Vector *vector) { 
	/*check nullable*/
	if (vector == NULL)
        return NULL;
	/*return the index 0 */
	return vector_get(vector, 0); }

void *vector_back(Vector *vector)
{
	/*check nullable*/
	if (vector == NULL)
        return NULL;
	/*return the index -1 */
    return vector_get(vector, vector->size - 1);
}

/* Information */
size_t vector_size(const Vector *vector) {
	if (vector == NULL)
        return 0; 
	/* Information */
	return vector->size; }

bool vector_is_empty(const Vector *vector) { /* Information */return vector->size == 0; }

/* Memory management */
int vector_resize(Vector *vector, size_t new_size)
{
	/* check whether vector is NULL. */
	if (vector == NULL)
        return VECTOR_ERROR;
	/* check whether vector has newsize. */
	if (vector->size ==new_size)
		return VECTOR_SUCCESS;
    /* check whether vector capacityL. */
    if (new_size > vector->capacity * VECTOR_MINIMUM_CAPACITY) {
		/* check whether vector capacity. */
        if (vector_align(vector, new_size * VECTOR_GROWTH_FACTOR) == VECTOR_ERROR) {
            return VECTOR_ERROR;
        }
    }

    vector->size = new_size;
    /* return. */
    return VECTOR_SUCCESS;
}

int vector_destroy(Vector *vector)
{
    /* check whether vector is NULL. */
    if (vector == NULL)
        return VECTOR_ERROR;
    /* free */
    free(vector->data);
    return VECTOR_SUCCESS;
}

/* Iterators */
Iterator vector_begin(Vector *vector)
{
	/* iterator implement */
    return vector_iterator(vector, 0);
}

Iterator vector_end(Vector *vector)
{
	/* iterator implement */
    return vector_iterator(vector, vector->size);
}

Iterator vector_iterator(Vector *vector, size_t index)
{
    Iterator iterator = {NULL, 0};
    /* check whether vector is NULL. */
    if (vector == NULL || index > vector->size || vector->element_size == 0)
        return iterator;

    /* pointer add */
    iterator.pointer = (char *)vector->data + (index * vector->element_size);
    iterator.element_size = vector->element_size;

    return iterator;
}

void *iterator_get(Iterator *iterator)
{
    /* iterator implement */
    return iterator->pointer;
}

void iterator_increment(Iterator *iterator)
{
    /* iterator implement */
    iterator->pointer = (char *)iterator->pointer + iterator->element_size;
}

void iterator_decrement(Iterator *iterator)
{
    /* iterator implement */
    iterator->pointer = (char *)iterator->pointer - iterator->element_size;
}

bool iterator_equals(Iterator *first, Iterator *second)
{
    /* iterator implement */
    return first->pointer == second->pointer;
}

/* Sort */
void vector_sort(Vector *vector, vector_less_func *less)
{
    int vector_outer_sort;
    int size;
	/* check nullable. */
	if (vector == NULL)
        return;
    /* get size */
    size = vector->size;
    /* bubble sort */
    vector_outer_sort = 0;
    while (vector_outer_sort < size - 1) {
        /* inner k defined */
        int vector_inner_sort = 0;
        while (vector_inner_sort < size - vector_outer_sort - 1) {
            /* get item */
            if (less(vector_get(vector, vector_inner_sort + 1),
                     vector_get(vector, vector_inner_sort))) {
                /* define item */
                int *temp;
                int temp_number;
                /* swap. */
                temp = vector_get(vector, vector_inner_sort + 1);
                temp_number = *temp;
                /* swap. */
                vector_assign(vector, vector_inner_sort + 1,
                              vector_get(vector, vector_inner_sort));
                vector_assign(vector, vector_inner_sort, &temp_number);
            }
            /* iteration */
            ++vector_inner_sort;
        }
        ++vector_outer_sort;
    }
}

/* Private */
int vector_align(Vector *vector, size_t new_capacity)
{
    void *old;
	/*check nullable*/
	if (vector == NULL)
        return VECTOR_ERROR;
    /* check whether vector is NULL. */
    if (new_capacity < VECTOR_MINIMUM_CAPACITY) {
        /* check whether is bigger than minimun capacity. */
        if (vector->capacity > VECTOR_MINIMUM_CAPACITY) {
            new_capacity = VECTOR_MINIMUM_CAPACITY;
        }
        /*or else*/
        else {
            return VECTOR_SUCCESS;
        }
    }
    /* get info. */
    new_capacity *= vector->element_size;
    old = vector->data;
    /* check whether vector is NULL. */
    if ((vector->data = malloc(new_capacity)) == NULL)
        return VECTOR_ERROR;
    /* get new data. */
    memcpy(vector->data, old, vector_size(vector) * vector->element_size);
    vector->capacity = new_capacity / vector->element_size;
    free(old);
    /*return*/
    return VECTOR_SUCCESS;
}

