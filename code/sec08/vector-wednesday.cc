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

/**
 * @brief defines the vector_t type.
 */
template <typename T>
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
	T& at(int pos);
	/**
	 * @brief Access the given element of the vector.
	 */
	T& operator[](int pos);
	/**
	 * @brief Overload equality operator.
	 */
	vector_t& operator=(const vector_t& other);

	template <typename S>
	friend std::ostream& operator << (std::ostream&, vector_t<S>&);
};

template <typename T>
vector_t<T>::vector_t()
	: data(NULL),
	  num_elem(0),
	  alloc_size(0)
{
}

template <typename T>
vector_t<T>::vector_t(const vector_t& other)
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

template <typename T>
vector_t<T>::~vector_t()
{
	delete[] data;
}

template <typename T>
void vector_t<T>::resize(size_t new_size)
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

template <typename T>
size_t vector_t<T>::size() const
{
	return num_elem;
}

template <typename T>
T& vector_t<T>::at(int pos)
{
	if(pos >= static_cast<int>(num_elem))
		throw std::out_of_range("position out of bounds!");
	if(pos < 0 and pos < - static_cast<int>(num_elem))
		throw std::out_of_range("position out of bounds from end!");
	if(pos < 0)
		return data[num_elem + pos];
	else
		return data[pos];
}

template <typename T>
T& vector_t<T>::operator[](int pos)
{
	return at(pos);
}

template <typename T>
vector_t<T>& vector_t<T>::operator=(const vector_t& other)
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

template <typename T>
std::ostream& operator << (std::ostream& other, vector_t<T>& vec)
{
	other << "vector of capacity " << vec.num_elem;
	other << ": {";
	other << vec[0];
	for (std::size_t i = 1; i < vec.size(); i++) {
		other << ", " << vec[i];
	}
	other << "}";
	return other;
}

std::ostream& operator << (std::ostream& other, foo& f)
{
	other << "foo";
	return other;
}

int main()
{
	vector_t<vector_t<foo>> vec;
	vec.resize(5);
	for(std::size_t i = 0; i < 5; i++) {
		vec[i].resize(5);
	}
	try {
		std::cout << vec << std::endl;
	} catch (std::out_of_range& e) {
		std::cout << "Out of range: " << e.what() << std::endl;
	} catch (std::bad_alloc& e) {
		std::cout << "Bad alloc: " << e.what() << std::endl;
	}
	vector_t<vector_t<foo>> vec2 = vec;
	return 0;
}
