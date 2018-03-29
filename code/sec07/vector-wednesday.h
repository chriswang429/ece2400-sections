#include <cstdlib>
#include <iostream>
#include <stdexcept>

typedef int T;

class vector_t { 
private:
  T* data;
  
  //size of data
  size_t num_elements;
  
  //allocated size
  size_t alloc_size;
  
public:
  
  vector_t();
  
  vector_t(const vector_t& other);
  
  ~vector_t();
  
  size_t size() const;
  
  void resize(size_t new_size);
  
  T& at(size_t index);
  
  T& operator[](size_t pos);
  
  vector_t& operator=(const vector_t& other);
  
  
};
