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

void test_arena_build_init(void)
{
	t_arena arena;

	arena_build(&arena);
	test_arena_print_check_null(&arena);
}

int main(void)
{
	test_arena_build_init();
	printf("\n");
}
