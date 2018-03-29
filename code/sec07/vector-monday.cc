/**
 * @file vector.cc
 */

#include <cstdlib>
#include <iostream>
#include <new>
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

typedef int T;

/**
 * @brief defines the vector_t type.
 */
class vector_t {
private:
	/** Pointer to data. */
	T* data;
	/** Size of the data. */
	size_t num_elem;
	/** Size of allocated data. */
	size_t alloc_size;
public:
	/**
	 * @brief Construct the vector.
	 */
	vector_t();
	/**
	 * @brief Copy constructor.
	 */
	vector_t(const vector_t& v);
	/**
	 * @brief Destroy a vector.
	 */
	~vector_t();
	/**
	 * @brief Resize the vector
	 *
	 * @param new_size New vector size.
	 * @throws std::bad_alloc if failure.
	 */
	void resize(size_t new_size);
	/**
	 * @brief Get the size of the vector.
	 */
	size_t size() const;
	/**
	 * @brief Access the given element of the vector.
	 */
	T& at(size_t pos);
	/**
	 * @brief Access the given element of the vector.
	 */
	T& operator[](size_t pos);
	/**
	 * @brief Overload equality operator.
	 */
	vector_t& operator=(const vector_t& other);
};

vector_t::vector_t()
	: data(NULL),
	  num_elem(0),
	  alloc_size(0)
{
}

vector_t::vector_t(const vector_t& other)
	: num_elem(other.num_elem),
	  alloc_size(other.num_elem)
{
	if(num_elem == 0) {
		data = NULL;
		return;
	}
	data = new T[num_elem];
	for(size_t i = 0; i < num_elem; i++) {
		data[i] = other.data[i];
	}
}

vector_t::~vector_t()
{
	delete[] data;
}

void vector_t::resize(size_t new_size)
{
	if(new_size > alloc_size) {
		T* new_data = new T[new_size];
		for(size_t i = 0; i < num_elem && i < new_size; i++) {
			new_data[i] = data[i];
		}
		delete[] data;
		data = new_data;
		num_elem = new_size;
	}
}

size_t vector_t::size() const
{
	return num_elem;
}

T& vector_t::at(size_t pos)
{
	if(pos >= num_elem)
		throw std::out_of_range("position out of bounds!");
	return data[pos];
}

T& vector_t::operator[](size_t pos)
{
	return at(pos);
}

vector_t& vector_t::operator=(const vector_t& other)
{
	if(data != NULL) {
		delete[] data;
		data = NULL;
		num_elem = 0;
		alloc_size = 0;
	}

	alloc_size = num_elem = other.num_elem;
	if(alloc_size != 0) {
		data = new T[alloc_size];
		for(size_t i = 0; i < alloc_size; i++) {
			data[i] = other.data[i];
		}
	}
	return *this;
}

int main()
{
	vector_t vec;
	vec.resize(5);
	vector_t vec2 = vec;
	vec.at(4) = 5;
	vec2[4] = 1000;
	vector_t vec3;
	vec3 = vec2;
	try {
		std::cout << vec.at(4) << std::endl;
		std::cout << vec2[4] << std::endl;
	} catch (std::out_of_range& e) {
		std::cout << "Out of range: " << e.what() << std::endl;
	} catch (std::bad_alloc& e) {
		std::cout << "Bad alloc: " << e.what() << std::endl;
	}
	return 0;
}
