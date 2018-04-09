#include "vector-wednesday.h"
#include <cstdlib>

vector_t::vector_t()
  :data(NULL),
  num_elements(0),
  alloc_size(0)
  {
  }
  
vector_t::vector_t(const vector_t& other) :
  num_elements(other.num_elements),
  alloc_size(other.alloc_size)
{
  if(num_elements == 0) {
    data = NULL;
    return;
  }
  
  data = new T[alloc_size];
  for(size_t i = 0; i < num_elements; ++i) {
    data[i] = other.data[i];
  } 
}

vector_t::~vector_t() {
  if(data != NULL) {
    delete[] data;
  }
}

void vector_t::resize(size_t new_size) {
  
  if(new_size > alloc_size) {
    T* new_data = new T[new_size];
    
    for(size_t i = 0; i<num_elements && i < new_size; ++i) {
      new_data[i] = data[i];
    }
    
    delete[] data;
    data = new_data;
    alloc_size = new_size;
    
  }
    num_elements = new_size;
}

size_t vector_t::size() const{
  return num_elements;
}

T& vector_t::at(size_t pos) {
  if(pos >= num_elements) {
    throw std::out_of_range("index out of bounds!");
  }
  
  return data[pos];
}

T& vector_t::operator[](size_t pos) {
  return at(pos);
}

vector_t& vector_t::operator=(const vector_t& other)
{
  if(data != NULL) {
    delete[] data;
    data = NULL;
    num_elements = 0;
    alloc_size = 0;
  }
  
  alloc_size = other.alloc_size;
  num_elements = other.num_elements;
  if(alloc_size != 0) {
    data = new T[alloc_size];
    for(size_t i = 0; i < alloc_size; ++i) {
      data[i] = other.data[i];
    }
  }
  
  return *this;
}

int main() {
  
  vector_t vec;
  vec.resize(5);
  vector_t vec2 = vec;
  vec.at(4) = 5;
  printf("%d\n", vec[4]);
  vec2[4] = 1000;
  printf("%d\n", vec2.at(4));
  std::cout << vec[4] << std::endl;
  
  vector_t vec3;
  vec3 = vec2;
  
  try{
    std::cout << vec.at(4) << std::endl;
    std::cout << vec2[4] << std::endl;
  } catch (std::out_of_range& e) {
    std::cout << "Out of range: " << e.what() << std::endl;
  } catch (std::bad_alloc& e) {
    std::cout << "Bad alloc: " << e.what() << std::endl;
  }
  return 0;
}
