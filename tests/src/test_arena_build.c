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

int test_arena_build_init()
{
	t_arena arena;
	int exit_status;

	arena_build(&arena);
	exit_status = test_arena_print_check_null(&arena);
	return (exit_status);
}

int main()
{
	RUN_TEST(test_arena_build_init);
	printf("\n");
}
