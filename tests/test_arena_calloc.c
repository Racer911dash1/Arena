#include "arena.h"
#include "colors.h"
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void test_arena_print_check_not_null(t_arena *arena)
{
	if (arena->head != NULL && arena->tail != NULL)
	{
		fprintf(stdout, GREEN "OK " RESET);
	}
	else
	{
		fprintf(stderr, RED "KO " RESET);
	}
}

void test_arena_calloc_zero_bytes()
{
	t_arena arena;

	arena_build(&arena);
	arena_calloc(&arena, 0, 0);
	test_arena_print_check_not_null(&arena);
	arena_destroy(&arena);
}

void test_arena_calloc_one_byte()
{
	t_arena arena;
	char *ptr;

	arena_build(&arena);
	ptr = arena_calloc(&arena, 1, 1);
	if (ptr == NULL)
	{
		fprintf(stderr, RED "KO " RESET);
	}
	if (*ptr == '\0')
	{
		fprintf(stdout, GREEN "OK " RESET);
	}
	else
	{
		fprintf(stderr, RED "KO " RESET);
	}
	arena_destroy(&arena);
}

void test_arena_calloc_buffer_size_one()
{
	t_arena arena;
	size_t size;
	char *ptr;

	arena_build(&arena);
	size = sysconf(_SC_PAGESIZE);
	ptr = arena_calloc(&arena, 1, size);
	if (ptr == NULL)
	{
		fprintf(stderr, RED "KO " RESET);
	}
	for (size_t i = 0; i < size; i += 1)
	{
		if (ptr[i] != '\0')
		{
			fprintf(stderr, RED "KO " RESET);
			return;
		}
	}
	test_arena_print_check_not_null(&arena);
	arena_destroy(&arena);
}

void test_arena_calloc_buffer_size_ten()
{
	t_arena arena;
	size_t size;
	char *ptr;

	arena_build(&arena);
	size = sysconf(_SC_PAGESIZE);
	for (size_t i = 0; i < 10; i += 1)
	{
		ptr = arena_calloc(&arena, 1, sysconf(_SC_PAGESIZE));
		if (ptr == NULL)
		{
			fprintf(stderr, RED "KO " RESET);
		}
		for (size_t ii = 0; ii < size; ii += 1)
		{
			if (ptr[ii] != '\0')
			{
				fprintf(stderr, RED "KO " RESET);
				return;
			}
		}
	}
	test_arena_print_check_not_null(&arena);
	arena_destroy(&arena);
}

void test_arena_calloc_buffer_size_plus_one_one()
{
	t_arena arena;
	size_t size;
	char *ptr;

	arena_build(&arena);
	size = sysconf(_SC_PAGESIZE) + 1;
	ptr = arena_calloc(&arena, 1, size);
	if (ptr == NULL)
	{
		fprintf(stderr, RED "KO " RESET);
		return;
	}
	for (size_t i = 0; i < size; i += 1)
	{
		if (ptr[i] != '\0')
		{
			fprintf(stderr, RED "KO " RESET);
			return;
		}
	}
	fprintf(stdout, GREEN "OK " RESET);
	arena_destroy(&arena);
}

void test_arena_calloc_buffer_size_plus_one_ten()
{
	t_arena arena;
	size_t size;
	char *ptr;

	arena_build(&arena);
	for (size_t i = 0; i < 10; i += 1)
	{
		size = sysconf(_SC_PAGESIZE) + 1;
		ptr = arena_calloc(&arena, 1, size);
		if (ptr == NULL)
		{
			fprintf(stderr, RED "KO " RESET);
			return;
		}
		for (size_t ii = 0; ii < size; ii += 1)
		{
			if (ptr[ii] != '\0')
			{
				fprintf(stderr, RED "KO " RESET);
				return;
			}
		}
	}
	fprintf(stdout, GREEN "OK " RESET);
	arena_destroy(&arena);
}

void test_arena_calloc_varying_sizes_ten()
{
	t_arena arena;
	size_t size;
	char *ptr;
	srand(time(NULL));

	arena_build(&arena);
	for (size_t i = 0; i < 10; i += 1)
	{
		size = rand() % sysconf(_SC_PAGESIZE) + 1;
		ptr = arena_calloc(&arena, 1, size);
		if (ptr == NULL)
		{
			fprintf(stderr, RED "KO " RESET);
			return;
		}
		for (size_t ii = 0; ii < size; ii += 1)
		{
			if (ptr[ii] != '\0')
			{
				fprintf(stderr, RED "KO " RESET);
				return;
			}
		}
	}
	fprintf(stdout, GREEN "OK " RESET);
	arena_destroy(&arena);
}

int main(void)
{
	test_arena_calloc_zero_bytes();
	test_arena_calloc_one_byte();
	test_arena_calloc_buffer_size_one();
	test_arena_calloc_buffer_size_ten();
	test_arena_calloc_buffer_size_plus_one_one();
	test_arena_calloc_buffer_size_plus_one_ten();
	test_arena_calloc_varying_sizes_ten();
	printf("\n");
}
