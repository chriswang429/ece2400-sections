/**
 * @file vector.c
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief defines the vector_t type.
 */
struct vector_t {
	/** Pointer to data. */
	int* data;
	/** Size of the data. */
	size_t size;
	/** Size of allocated data. */
	size_t alloc_size;
};

/**
 * @brief Construct the vector.
 */
void vector_init(struct vector_t* vec)
{
	if(vec == NULL) return;
	vec->data = NULL;
	vec->size = 0;
	vec->alloc_size = 0;
}

/**
 * @brief Destroy a vector.
 */
void vector_destroy(struct vector_t* vec)
{
	if(vec == NULL) return;
	free(vec->data);
	vec->data = NULL;
	vec->size = 0;
	vec->alloc_size = 0;
}

/**
 * @brief Resize the vector
 *
 * @param new_size New vector size.
 * @returns non-zero if failure
 * @returns 0 if success
 */
int vector_resize(struct vector_t* vec, size_t new_size)
{
	if(vec == NULL) return 1;
	if(new_size > vec->alloc_size) {
		int* new_data = realloc(vec->data, new_size * sizeof(int));
		printf("realloc\n");
		if(new_data != NULL) {
			vec->data = new_data;
			vec->size = new_size;
			vec->alloc_size = new_size;
			return 0;
		} else {
			perror("realloc() failed");
			return 1;
		}
	} else {
		vec->size = new_size;
	}
}

/**
 * @brief Get the size of the vector.
 */
size_t vector_get_size(const struct vector_t* vec)
{
	if(vec == NULL) return 0;
	return vec->size;
}

/**
 * @brief Return an element at specified position.
 */
int vector_get_elem(const struct vector_t* vec, size_t pos)
{
	if(vec == NULL) return 0;
	if(pos < vec->size)
		return vec->data[pos];
	return 0;
}

/**
 * @brief Set element of vector at specified position.
 */
void vector_set_elem(struct vector_t* vec, size_t pos, int value)
{
	if(vec == NULL) return;
	if(pos >= vec->size)
		vector_resize(vec, pos + 1);
	if(pos < vec->size)
		vec->data[pos] = value;
}

int main()
{
	struct vector_t* vec;
	vec = malloc(sizeof(struct vector_t));
	vector_init(vec);
	vector_resize(vec, 5);
	vector_set_elem(vec, 81, 7);
	vector_resize(vec, 5);
//	printf("%d\n", vector_get_elem(vec, pos));
	vector_destroy(vec);
	free(vec);
	return 0;
}
