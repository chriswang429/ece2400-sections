#include <cstdlib>
#include <iostream>
#include <stdexcept>

class foo {
public:
	foo()
	{
		std::cout << "Foo::Constructor" << std::endl;
	}
	~foo()
	{
		std::cout << "Foo::destructor" << std::endl;
	}
};

template<typename T>
class vector_t { 
private:

  T* data;
  
  //size of data
  size_t num_elements;
  
  //allocated size
  size_t alloc_size;
  
public:
  
  vector_t<T>();
  
  vector_t<T>(const vector_t<T>& other);
  
  ~vector_t<T>();
  
  size_t size() const;
  
  void resize(size_t new_size);
  
  T& at(size_t index);
  
  T& operator[](size_t pos);
  
  vector_t<T>& operator=(const vector_t<T>& other);
  
  vector_t<T>& operator+(vector_t<T>& rhs);
  
};

template<typename T>
std::ostream& operator <<(std::ostream& os, vector_t<T> vec) {
  for(size_t i = 0; i < vec.size(); ++i) {
    os << vec[i] << std::endl;
  }
  return os;
}

std::ostream& operator <<(std::ostream& os, foo f) {
  os << "foo" << std::endl;
}

template<typename T>
vector_t<T>::vector_t()
  :data(NULL),
  num_elements(0),
  alloc_size(0)
{
}
  
template<typename T>
vector_t<T>::vector_t(const vector_t& other) :
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

template<typename T>
vector_t<T>::~vector_t() {
  if(data != NULL) {
    delete[] data;
  }
}

template<typename T>
void vector_t<T>::resize(size_t new_size) {
  
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

template<typename T>
size_t vector_t<T>::size() const{
  return num_elements;
}

template<typename T>
T& vector_t<T>::at(size_t pos) {
  if(pos >= num_elements) {
    throw std::out_of_range("index out of bounds!");
  }
  
  return data[pos];
}

template<typename T>
T& vector_t<T>::operator[](size_t pos) {
  return at(pos);
}

template<typename T>
vector_t<T>& vector_t<T>::operator=(const vector_t<T>& other)
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

template<typename T>
vector_t<T>& vector_t<T>::operator +(vector_t<T>& rhs) {
  
  vector_t<T> newVec;
  
  newVec.resize(num_elements + rhs.num_elements);
  
  for(size_t i = 0; i < newVec.num_elements; ++i) {
    
    if(i < num_elements) {
      newVec[i] = data[i];
    } else {
      newVec[i] = rhs[i-num_elements];    
    }
    
  }
  
  *this = newVec;
  
  return *this;
  
}
