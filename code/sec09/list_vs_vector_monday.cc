#include <chrono>
#include <cstddef>
#include <iostream>
#include <list>
#include <vector>

#include "time_to_string.h"

int main()
{
	const std::size_t num_elem = 0x100000;
	auto start_list = std::chrono::steady_clock::now();
	std::list<int> list;
	for(std::size_t i = 0; i < num_elem; i++) {
		list.emplace_back(i);
	}
	auto   end_list = std::chrono::steady_clock::now();
	std::cout << "List took "
		<< ece2400::time_to_string(end_list - start_list)
		<< std::endl;

	auto start_vec  = std::chrono::steady_clock::now();
	std::vector<int> vector;
	for(std::size_t i = 0; i < num_elem; i++) {
		vector.emplace_back(i);
	}
	auto   end_vec  = std::chrono::steady_clock::now();
	std::cout << "Vector took "
		<< ece2400::time_to_string(end_vec - start_vec)
		<< std::endl;
	return 0;
}
