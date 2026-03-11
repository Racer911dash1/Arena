#include "test_arena.h"

int test_arena_print_check_null(t_arena *arena)
{
	if (arena->head != NULL || arena->tail != NULL)
	{
		return (EXIT_FAILURE);
	}
	else
	{
		return (EXIT_SUCCESS);
	}
}

int test_arena_destroy_empty()
{
	t_arena arena;
	int exit_status;

	arena_build(&arena);
	arena_destroy(&arena);
	exit_status = test_arena_print_check_null(&arena);
	return (exit_status);
}

int test_arena_destroy_single_alloc()
{
	t_arena arena;
	int exit_status;

	arena_build(&arena);
	arena_malloc(&arena, 1);
	arena_destroy(&arena);
	exit_status = test_arena_print_check_null(&arena);
	return (exit_status);
}

int test_arena_destroy_many_alloc()
{
	t_arena arena;
	int exit_status;

	arena_build(&arena);
	for (size_t i = 0; i < 10; i += 1)
	{
		arena_malloc(&arena, sysconf(_SC_PAGESIZE) + 1);
	}
	arena_destroy(&arena);
	exit_status = test_arena_print_check_null(&arena);
	return (exit_status);
}

int main()
{
	RUN_TEST(test_arena_destroy_empty);
	RUN_TEST(test_arena_destroy_single_alloc);
	RUN_TEST(test_arena_destroy_many_alloc);
	printf("\n");
}
