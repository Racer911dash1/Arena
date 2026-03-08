#include "arena.h"
#include "colors.h"
#include <stdio.h>
#include <unistd.h>

void test_arena_print_check_null(t_arena *arena)
{
	if (arena->head != NULL || arena->tail != NULL)
	{
		fprintf(stderr, RED "KO " RESET);
	}
	else
	{
		fprintf(stdout, GREEN "OK " RESET);
	}
}

void test_arena_destroy_empty(void)
{
	t_arena arena;

	arena_build(&arena);
	arena_destroy(&arena);
	test_arena_print_check_null(&arena);
}

void test_arena_destroy_uninitialized()
{
	t_arena arena;

	arena_destroy(&arena);
	test_arena_print_check_null(&arena);
}

void test_arena_destroy_single_alloc()
{
	t_arena arena;

	arena_build(&arena);
	arena_malloc(&arena, 1);
	arena_destroy(&arena);
	test_arena_print_check_null(&arena);
}

void test_arena_destroy_many_alloc()
{
	t_arena arena;

	arena_build(&arena);
	for (size_t i = 0; i < 10; i += 1)
	{
		arena_malloc(&arena, sysconf(_SC_PAGESIZE) + 1);
	}
	arena_destroy(&arena);
	test_arena_print_check_null(&arena);
}

int main(void)
{
	test_arena_destroy_empty();
	test_arena_destroy_uninitialized(); // Seems unsafe, don't know how else to check
	test_arena_destroy_single_alloc();
	test_arena_destroy_many_alloc();
	printf("\n");
}
