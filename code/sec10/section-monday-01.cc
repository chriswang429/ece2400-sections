#include <chrono>
#include <cstddef>
#include <iostream>
#include <pthread.h>

#include "time_to_string.h"

using steady_clock = std::chrono::steady_clock;

struct incr_x_args {
	int& x;
	pthread_mutex_t& mutex;
};

void* incr_x(void* i)
{
	int x = 0;
	incr_x_args* input = reinterpret_cast<incr_x_args*>(i);
	for(std::size_t i = 0; i < 10000; i++) {
		x++;
	}
	pthread_mutex_lock(&input->mutex);
	input->x += x;
	pthread_mutex_unlock(&input->mutex);
	return nullptr;
}

int main(void)
{
	int x = 0;
	auto start = steady_clock::now();
	pthread_t threads[4];
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, nullptr);
	incr_x_args x_args{x, mutex};
	for(std::size_t i = 0; i < 4; i++){
		pthread_create(
			&threads[i], nullptr,
			&incr_x, &x_args
			);
	}
	for(std::size_t i = 0; i < 4; i++) {
		pthread_join(threads[i], nullptr);
	}
	auto end   = steady_clock::now();
	pthread_mutex_destroy(&mutex);
	std::cout << "x is " << x << std::endl;
	std::cout << "Took " << ece2400::time_to_string(end - start)
		<< std::endl;
	return 0;
}
