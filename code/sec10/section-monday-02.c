#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	size_t board_size;
	size_t start;
	size_t end;
	size_t num_sols;
} nqueens_args;

size_t nqueens_h(unsigned char* board, size_t board_size, size_t k)
{
	size_t num_sols = 0;
	if(k >= board_size) return 1;
	for(size_t i = 0; i < board_size; i++) {
		int cannot_place = 0;
		for(size_t j = 0; j < k; j++) {
			// Vertical conflict;
			if(board[j] == i) {
				cannot_place = 1;
				break;
			}
			// Left diagonal conflict;
			if(i > board[j] && i - board[j] == k - j) {
				cannot_place = 1;
				break;
			}
			// Right diagonal conflict;
			if(i < board[j] && board[j] - i == k - j) {
				cannot_place = 1;
				break;
			}
		}
		if(! cannot_place) {
			board[k] = (unsigned char) i;
			num_sols += nqueens_h(board, board_size, k + 1);
		}
	}
	return num_sols;
}

void* pnqueens(void* args)
{
	nqueens_args* n_args = (nqueens_args*) args;
	unsigned char board[n_args->board_size];
	size_t num_sols = 0;
	for(
		size_t i = n_args->start;
		i < n_args->board_size && i < n_args->end;
		i++
		) {
		board[0] = (unsigned char) i;
		num_sols += nqueens_h(board, n_args->board_size, 1);
	}
	n_args->num_sols = num_sols;
	return NULL;
}

size_t nqueens(size_t board_size, size_t num_threads)
{
	if(board_size > 15) return -1;
	size_t num_sols = 0;
	pthread_t threads[num_threads];
	nqueens_args args[num_threads];
	size_t cols_per_thread = (board_size + num_threads - 1) / num_threads;
	for(size_t i = 0; i < num_threads; i++) {
		args[i].board_size = board_size;
		args[i].start = i * cols_per_thread;
		args[i].end = (i + 1) * cols_per_thread;
		args[i].num_sols = 0;
	}
	for(size_t i = 0; i < num_threads; i++) {
		pthread_create(
			&threads[i], NULL,
			&pnqueens, &args[i]
			);
	}
	for(size_t i = 0; i < num_threads; i++) {
		pthread_join(threads[i], NULL);
		num_sols += args[i].num_sols;
	}
	return num_sols;
}

int main(int argc, char** argv)
{
	if(argc != 3) {
		fprintf(stderr, "Usage: %s board_size num_threads\n", argv[0]);
		return 1;
	}
	size_t board_size = atoi(argv[1]);
	size_t num_threads = atoi(argv[2]);
	printf("nqueens(%d) = %d\n", board_size, nqueens(board_size, num_threads));
	return 0;
}
