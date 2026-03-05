#include "arena.h"
#include "colors.h"
#include <assert.h>
#include <stdio.h>
#include <time.h>

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

	arena_build(&arena);
	arena_calloc(&arena, 1, 1);
	test_arena_print_check_not_null(&arena);
	arena_destroy(&arena);
}

void test_arena_calloc_buffer_size_one()
{
	t_arena arena;

	arena_build(&arena);
	arena_calloc(&arena, 1, ARENA_BUFFER_SIZE);
	test_arena_print_check_not_null(&arena);
	arena_destroy(&arena);
}

void test_arena_calloc_buffer_size_ten()
{
	t_arena arena;

	arena_build(&arena);
	for (size_t i = 0; i < 10; i++)
	{
		arena_calloc(&arena, 1, ARENA_BUFFER_SIZE);
	}
	test_arena_print_check_not_null(&arena);
	arena_destroy(&arena);
}

void test_arena_calloc_buffer_size_plus_one_one()
{
	t_arena arena;

	arena_build(&arena);
	arena_calloc(&arena, 1, ARENA_BUFFER_SIZE + 1);
	test_arena_print_check_not_null(&arena);
	arena_destroy(&arena);
}

void test_arena_calloc_buffer_size_plus_one_ten()
{
	t_arena arena;

	arena_build(&arena);
	for (size_t i = 0; i < 10; i++)
	{
		arena_calloc(&arena, 1, ARENA_BUFFER_SIZE + 1);
	}
	test_arena_print_check_not_null(&arena);
	arena_destroy(&arena);
}

void test_arena_calloc_varying_sizes_ten()
{
	t_arena arena;
	srand(time(NULL));

	arena_build(&arena);
	for (size_t i = 0; i < 10; i++)
	{
		arena_calloc(&arena, 1, rand() % ARENA_BUFFER_SIZE + 1);
	}
	test_arena_print_check_not_null(&arena);
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
