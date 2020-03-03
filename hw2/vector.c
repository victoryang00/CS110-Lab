#include <stdlib.h>
#include <string.h>
#include "vector.h"

int vector_init(Vector* vector, size_t capacity, size_t element_size) {
	if (vector == NULL) return VECTOR_ERROR;

	vector->size = 0;
	vector->capacity = MAX(VECTOR_MINIMUM_CAPACITY, capacity);
	vector->element_size = element_size;
	vector->data = malloc(vector->capacity * element_size);

	return vector->data == NULL ? VECTOR_ERROR : VECTOR_SUCCESS;
}

int vector_copy(Vector* destination, Vector* source) {
	if (destination == NULL||source == NULL||vector_is_initialized(destination)||!vector_is_initialized(source)) return VECTOR_ERROR;

	/* Copy ALL the data */
	destination->size = source->size;
	destination->capacity = source->size * 2;
	destination->element_size = source->element_size;

	destination->data = malloc(destination->capacity * source->element_size);
	if (destination->data == NULL) return VECTOR_ERROR;

	memcpy(destination->data, source->data, vector_byte_size(source));

	return VECTOR_SUCCESS;
}

/* Insertion */
int vector_push_back(Vector* vector, void* element) {
	if (vector->size == vector->capacity&& _vector_adjust_capacity(vector) == VECTOR_ERROR) return VECTOR_ERROR;

	_vector_assign(vector, vector->size, element);
	++vector->size;

	return VECTOR_SUCCESS;
}

int vector_push_front(Vector* vector, void* element) {
	return vector_insert(vector, 0, element);
}

int vector_insert(Vector* vector, size_t index, void* element) {
	void* offset;

	if (vector == NULL||element == NULL||vector->element_size == 0||index > vector->size) return VECTOR_ERROR;

	if ((vector->size == vector->capacity&&_vector_adjust_capacity(vector) == VECTOR_ERROR)||_vector_move_right(vector, index) == VECTOR_ERROR) return VECTOR_ERROR;

	/* Insert the element */
	offset = _vector_offset(vector, index);
	memcpy(offset, element, vector->element_size);
	++vector->size;

	return VECTOR_SUCCESS;
}

int vector_assign(Vector* vector, size_t index, void* element) {
    if (vector == NULL||element == NULL||vector->element_size == 0||index > vector->size) return VECTOR_ERROR;

	_vector_assign(vector, index, element);

	return VECTOR_SUCCESS;
}

/* Deletion */
int vector_pop_back(Vector* vector) {

	if (vector == NULL||vector->element_size == 0) return VECTOR_ERROR;

	--vector->size;

	if (vector->size == vector->capacity * VECTOR_MINIMUM_CAPACITY) 	_vector_adjust_capacity(vector);

	return VECTOR_SUCCESS;
}

int vector_pop_front(Vector* vector) {
	return vector_erase(vector, 0);
}

int vector_erase(Vector* vector, size_t index) {
	if (vector == NULL) return VECTOR_ERROR;
	if (vector->element_size == 0) return VECTOR_ERROR;
	if (index >= vector->size) return VECTOR_ERROR;

	/* Just overwrite */
	_vector_move_left(vector, index);

	if (--vector->size == vector->capacity / 4) {
		_vector_adjust_capacity(vector);
	}

	return VECTOR_SUCCESS;
}

int vector_clear(Vector* vector) {
	return vector_resize(vector, 0);
}

/* Lookup */
void* vector_get(Vector* vector, size_t index) {
	if (vector == NULL||vector->element_size == 0||index >= vector->size) return NULL;

	return _vector_offset(vector, index);
}


void* vector_front(Vector* vector) {
	return vector_get(vector, 0);
}

void* vector_back(Vector* vector) {
	return vector_get(vector, vector->size - 1);
}

/* Information */
bool vector_is_initialized(const Vector* vector) {
	return vector->data != NULL;
}

size_t vector_byte_size(const Vector* vector) {
	return vector->size * vector->element_size;
}

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
		if (_vector_reallocate(vector, new_size * VECTOR_GROWTH_FACTOR) == -1) {
			return VECTOR_ERROR;
		}
	} else if (new_size > vector->capacity) {
		if (_vector_reallocate(vector, new_size * VECTOR_GROWTH_FACTOR) == -1) {
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

	iterator.pointer = _vector_offset(vector, index);
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

void* iterator_next(Iterator* iterator) {
	void* current = iterator->pointer;
	iterator_increment(iterator);

	return current;
}

bool iterator_equals(Iterator* first, Iterator* second) {
	return first->pointer == second->pointer;
}

int iterator_erase(Vector* vector, Iterator* iterator) {
    size_t index = iterator_index(vector, iterator);

    if (vector_erase(vector, index) == VECTOR_ERROR) {
        return VECTOR_ERROR;
    }

    *iterator = vector_iterator(vector, index);

    return VECTOR_SUCCESS;
}

size_t iterator_index(Vector* vector, Iterator* iterator) {
    return (iterator->pointer - vector->data) / vector->element_size;
}

/* Sort */
void vector_sort(Vector *vector, vector_less_func *less){
	int i=0;
	int size=vector->size;
	while(i<size-1){
		int k=0;
		while(k<size-i-1){
			if(less(vector_get(vector,k),vector_get(vector,k+1))){
				int *t=vector_get(vector,k+1);
				int a=*t;
				vector_assign(vector,k+1,vector_get(vector,k));
				vector_assign(vector,k,&a);
			}
			k++;
		}
		i++;
	}
}

/* private */
void* _vector_offset(Vector* vector, size_t index) {
	return (char*)vector->data + (index * vector->element_size);
}

void _vector_assign(Vector* vector, size_t index, void* element) {
	void* offset = _vector_offset(vector, index);
	memcpy(offset, element, vector->element_size);
}

int _vector_move_right(Vector* vector, size_t index) {
	/* The location where to start to move from. */
	void* offset = _vector_offset(vector, index);

	/* How many to move to the right. */
	size_t elements_in_bytes = (vector->size - index) * vector->element_size;

	memmove((char*)offset + vector->element_size, offset, elements_in_bytes);
	return VECTOR_SUCCESS;
}

void _vector_move_left(Vector* vector, size_t index) {
	size_t right_elements_in_bytes;
	void* offset;

	/* The offset into the memory */
	offset = _vector_offset(vector, index);

	/* How many to move to the left */
	right_elements_in_bytes = (vector->size - index - 1) * vector->element_size;

	memmove(offset, (char*)offset + vector->element_size, right_elements_in_bytes);
}

int _vector_adjust_capacity(Vector* vector) {
	return _vector_reallocate(vector,MAX(1, vector->size * VECTOR_GROWTH_FACTOR));
}

int _vector_reallocate(Vector* vector, size_t new_capacity) {
	size_t new_capacity_in_bytes;
	void* old;

	if (new_capacity < VECTOR_MINIMUM_CAPACITY) {
		if (vector->capacity > VECTOR_MINIMUM_CAPACITY) {
			new_capacity = VECTOR_MINIMUM_CAPACITY;
		} else {
			return VECTOR_SUCCESS;
		}
	}

	new_capacity_in_bytes = new_capacity * vector->element_size;
	old = vector->data;

	if ((vector->data = malloc(new_capacity_in_bytes)) == NULL) {
		return VECTOR_ERROR;
	}

	memcpy(vector->data, old, vector_byte_size(vector));


	vector->capacity = new_capacity;

	free(old);

	return VECTOR_SUCCESS;
}
