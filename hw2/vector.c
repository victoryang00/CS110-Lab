#include <stdlib.h>
#include <string.h>
#include "vector.h"
/* define PRIVATE func. */
int vector_align(Vector* vector,size_t new_capacity);

int vector_init(Vector* vector, size_t capacity, size_t element_size) {
	if (vector == NULL) return VECTOR_ERROR;

	vector->size = 0;
	vector->capacity = MAX(VECTOR_MINIMUM_CAPACITY, capacity);
	vector->element_size = element_size;
	vector->data = malloc(vector->capacity * element_size);

	return vector->data == NULL ? VECTOR_ERROR : VECTOR_SUCCESS;
}

int vector_copy(Vector* destination, Vector* source) {
	if (destination == NULL||source == NULL||destination->data != NULL||!(source->data != NULL)) return VECTOR_ERROR;

	/* Copy ALL the data */
	destination->size = source->size;
	destination->capacity = source->size * 2;
	destination->element_size = source->element_size;

	destination->data = malloc(destination->capacity * source->element_size);
	if (destination->data == NULL) return VECTOR_ERROR;

	memcpy(destination->data, source->data, vector_size(source)*source->size);

	return VECTOR_SUCCESS;
}

/* Insertion */
int vector_push_back(Vector* vector, void* element) {
	int index;
	void* offset;
	if (vector->size == vector->capacity&& vector_align(vector,MAX(1, vector->size * VECTOR_GROWTH_FACTOR)) == VECTOR_ERROR) 
		return VECTOR_ERROR;
	
	index=vector->size;
    offset = (char*)vector->data + (index * vector->element_size);
	memcpy(offset, element, vector->element_size);
	++vector->size;

	return VECTOR_SUCCESS;
}

int vector_push_front(Vector* vector, void* element) {
	return vector_insert(vector, 0, element);
}

int vector_insert(Vector* vector, size_t index, void* element) {
	void* offset;
	size_t elements_bit;

	if (vector == NULL||element == NULL||vector->element_size == 0||index > vector->size) return VECTOR_ERROR;

	if ((vector->size == vector->capacity&&vector_align(vector,MAX(1, vector->size * VECTOR_GROWTH_FACTOR)) == VECTOR_ERROR)) return VECTOR_ERROR;

	/* move right. */
	offset = (char*)vector->data + (index * vector->element_size);
	elements_bit = (vector->size - index) * vector->element_size;
	memmove((char*)offset + vector->element_size, offset, elements_bit);

	/* insert the element */
	offset = (char*)vector->data + (index * vector->element_size);
	memcpy(offset, element, vector->element_size);
	++vector->size;

	return VECTOR_SUCCESS;
}

int vector_assign(Vector* vector, size_t index, void* element) {
	void* offset;

    if (vector == NULL||element == NULL||vector->element_size == 0||index > vector->size) return VECTOR_ERROR;

	offset = (char*)vector->data + (index * vector->element_size);
	memcpy(offset, element, vector->element_size);

	return VECTOR_SUCCESS;
}

/* Deletion */
int vector_pop_back(Vector* vector) {

	if (vector == NULL||vector->element_size == 0) return VECTOR_ERROR;

	--vector->size;

	if (vector->size == vector->capacity * VECTOR_MINIMUM_CAPACITY) 	vector_align(vector,MAX(1, vector->size * VECTOR_GROWTH_FACTOR));

	return VECTOR_SUCCESS;
}

int vector_pop_front(Vector* vector) {
	return vector_erase(vector, 0);
}

int vector_erase(Vector* vector, size_t index) {
	size_t right;
	void* offset;
	if (vector == NULL||vector->element_size == 0||index >= vector->size) return VECTOR_ERROR;

	offset = (char*)vector->data + (index * vector->element_size);
	right = (vector->size - index - 1) * vector->element_size;

	memmove(offset, (char*)offset + vector->element_size, right);

	if (--vector->size == vector->capacity / 4) {
		vector_align(vector,MAX(1, vector->size * VECTOR_GROWTH_FACTOR));
	}

	return VECTOR_SUCCESS;
}

int vector_clear(Vector* vector) {
	return vector_resize(vector, 0);
}

/* Lookup */
void* vector_get(Vector* vector, size_t index) {
	if (vector == NULL||vector->element_size == 0||index >= vector->size) return NULL;

	return (char*)vector->data + (index * vector->element_size);
}


void* vector_front(Vector* vector) {
	return vector_get(vector, 0);
}

void* vector_back(Vector* vector) {
	return vector_get(vector, vector->size - 1);
}

/* Information */
size_t vector_size(const Vector* vector){
	return vector->size;
}

bool vector_is_empty(const Vector* vector) {
	return vector->size == 0;
}

/* Memory management */
int vector_resize(Vector* vector, size_t new_size) {
	if (new_size <= vector->capacity * VECTOR_MINIMUM_CAPACITY) {
		vector->size = new_size;
		if (vector_align(vector, new_size * VECTOR_GROWTH_FACTOR) == -1) {
			return VECTOR_ERROR;
		}
	} else if (new_size > vector->capacity) {
		if (vector_align(vector, new_size * VECTOR_GROWTH_FACTOR) == -1) {
			return VECTOR_ERROR;
		}
	}

	vector->size = new_size;

	return VECTOR_SUCCESS;
}

int vector_destroy(Vector* vector) {
    if (vector == NULL) return VECTOR_ERROR;

    free(vector->data);
    vector->data = NULL;

    return VECTOR_SUCCESS;
}

/* Iterators */
Iterator vector_begin(Vector* vector) {
	return vector_iterator(vector, 0);
}

Iterator vector_end(Vector* vector) {
	return vector_iterator(vector, vector->size);
}

Iterator vector_iterator(Vector* vector, size_t index) {
	Iterator iterator = {NULL, 0};
	if (vector == NULL) return iterator;
	if (index > vector->size) return iterator;
	if (vector->element_size == 0) return iterator;

	iterator.pointer = (char*)vector->data + (index * vector->element_size);
	iterator.element_size = vector->element_size;

	return iterator;
}

void* iterator_get(Iterator* iterator) {
	return iterator->pointer;
}

void iterator_increment(Iterator* iterator) {
    iterator->pointer = (char*)iterator->pointer + iterator->element_size;
}

void iterator_decrement(Iterator* iterator) {
    iterator->pointer = (char*)iterator->pointer - iterator->element_size;
}

bool iterator_equals(Iterator* first, Iterator* second) {
	return first->pointer == second->pointer;
}

/* Sort */
void vector_sort(Vector *vector, vector_less_func *less){
	int vector_outer_sort;
	int size;
	
	size=vector->size;

	vector_outer_sort = 0;
	while(vector_outer_sort<size-1){
		int vector_inner_sort=0;
		while(vector_inner_sort<size-vector_outer_sort-1){
			if(less(vector_get(vector,vector_inner_sort),vector_get(vector,vector_inner_sort+1))){
				int *temp;
				int temp_number;
				temp=vector_get(vector,vector_inner_sort+1);
				temp_number = *temp;
				vector_assign(vector,vector_inner_sort+1,vector_get(vector,vector_inner_sort));
				vector_assign(vector,vector_inner_sort,&temp_number);
			}
			++vector_inner_sort;
		}
		++vector_outer_sort;
	}
}

/* Private */
int vector_align(Vector* vector,size_t new_capacity) {
	void* old;

	if (new_capacity < VECTOR_MINIMUM_CAPACITY) {
		if (vector->capacity > VECTOR_MINIMUM_CAPACITY) {
			new_capacity = VECTOR_MINIMUM_CAPACITY;
		} else {
			return VECTOR_SUCCESS;
		}
	}

	new_capacity *= vector->element_size;
	old = vector->data;

	if ((vector->data = malloc(new_capacity)) == NULL) return VECTOR_ERROR;

	memcpy(vector->data, old, vector_size(vector)*vector->element_size);
	vector->capacity = new_capacity/vector->element_size;
	free(old);

	return VECTOR_SUCCESS;
}
