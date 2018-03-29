#include <stdio.h>
#include <stdlib.h>

struct vector_t {
  int* data;
  size_t size;
  size_t alloc_size;
};

void vector_init(struct vector_t* vec) {
  if(vec == NULL) return;
  vec->data = NULL;
  vec->size = 0;
  vec->alloc_size = 0;
}

void vector_destroy(struct vector_t* vec) {
  if(vec == NULL) return;
  free(vec->data);
  vec->data = NULL;
  vec->size = 0;
  vec->alloc_size = 0;
}

int vector_resize(struct vector_t* vec, size_t size) {
  if(vec == NULL) return 1;
  if(size > vec->size) {
    vec->data = realloc(vec->data, size * sizeof(int));
    if(vec->data == NULL) {
      perror("realloc() failed");
      return 1;
    }
    vec->alloc_size = size;
    vec->size = size;
  }else if(size == 0) {
      vector_destroy(vec);
  }else {
    vec->size = size;
  }
  
  return 0;
}

size_t vector_get_size(struct vector_t* vec) {
  if(vec == NULL) return 0;
  return vec->size;
}

int vector_get_element(const struct vector_t* vec, size_t index) {
  if(vec == NULL) return 0;
  if(index < vec->size) {
    return vec->data[index];
  }
  return 0;
}

void vector_set_element(struct vector_t* vec, size_t pos, int value) {
  if(vec == NULL) return;
  if(pos < vec->alloc_size) {
    vec->data[pos] = value;
    if(vec->size <= pos) {
      vec->size = pos+1;
    }
  } else {
    vector_resize(vec, pos+1);
    vec->data[pos] = value;
  }
}

int main() {
  struct vector_t* vec;
  vec = malloc(sizeof(struct vector_t));
  vector_init(vec);
  vector_resize(vec, 5);
  vector_set_element(vec, 0, 42);
  //printf("%d\n", vector_get_element(vec,0));
  vector_set_element(vec, 42, 1);
  //printf("size is %d\n", vec->size);
  //printf("element 42 is %d\n", vector_get_element(vec,42));
  vector_resize(vec, 5);
  //printf("size is %d\n", vec->size);
  vector_destroy(vec);
  free(vec);
  return 0;
}
