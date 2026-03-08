#include "arena.h"
#include "colors.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
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

void test_arena_malloc_zero_bytes()
{
	t_arena arena;

	arena_build(&arena);
	arena_malloc(&arena, 0);
	test_arena_print_check_not_null(&arena);
	arena_destroy(&arena);
}

void test_arena_malloc_one_byte()
{
	t_arena arena;

	arena_build(&arena);
	arena_malloc(&arena, 1);
	test_arena_print_check_not_null(&arena);
	arena_destroy(&arena);
}

void test_arena_malloc_buffer_size_one()
{
	t_arena arena;

	arena_build(&arena);
	arena_malloc(&arena, sysconf(_SC_PAGESIZE));
	test_arena_print_check_not_null(&arena);
	arena_destroy(&arena);
}

void test_arena_malloc_buffer_size_ten()
{
	t_arena arena;

	arena_build(&arena);
	for (size_t i = 0; i < 10; i += 1)
	{
		arena_malloc(&arena, sysconf(_SC_PAGESIZE));
	}
	test_arena_print_check_not_null(&arena);
	arena_destroy(&arena);
}

void test_arena_malloc_buffer_size_plus_one_one()
{
	t_arena arena;

	arena_build(&arena);
	arena_malloc(&arena, sysconf(_SC_PAGESIZE) + 1);
	test_arena_print_check_not_null(&arena);
	arena_destroy(&arena);
}

void test_arena_malloc_buffer_size_plus_one_ten()
{
	t_arena arena;

	arena_build(&arena);
	for (size_t i = 0; i < 10; i += 1)
	{
		arena_malloc(&arena, sysconf(_SC_PAGESIZE) + 1);
	}
	test_arena_print_check_not_null(&arena);
	arena_destroy(&arena);
}

void test_arena_malloc_varying_sizes_ten()
{
	t_arena arena;
	srand(time(NULL));

	arena_build(&arena);
	for (size_t i = 0; i < 10; i += 1)
	{
		arena_malloc(&arena, rand() % sysconf(_SC_PAGESIZE) + 1);
	}
	test_arena_print_check_not_null(&arena);
	arena_destroy(&arena);
}

void test_arena_malloc_pointer_comparison()
{
	t_arena arena;
	char *ptr1;
	char *ptr2;

	arena_build(&arena);
	ptr1 = arena_malloc(&arena, 4 * sizeof(char));
	ptr2 = arena_malloc(&arena, 4 * sizeof(char));
	if (ptr1 == ptr2)
	{
		fprintf(stderr, RED "KO " RESET);
	}
	else
	{
		fprintf(stdout, GREEN "OK " RESET);
	}
	arena_destroy(&arena);
}

int main(void)
{
	test_arena_malloc_zero_bytes();
	test_arena_malloc_one_byte();
	test_arena_malloc_buffer_size_one();
	test_arena_malloc_buffer_size_ten();
	test_arena_malloc_buffer_size_plus_one_one();
	test_arena_malloc_buffer_size_plus_one_ten();
	test_arena_malloc_varying_sizes_ten();
	test_arena_malloc_pointer_comparison();
	printf("\n");
}
