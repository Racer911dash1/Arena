#include "arena.h"
#include "colors.h"
#include <assert.h>
#include <stdio.h>

void test_arena_print_check_strtrim(char *trim, char *compare)
{
	if (strcmp(trim, compare) == 0)
	{
		fprintf(stdout, GREEN "OK " RESET);
	}
	else
	{
		fprintf(stderr, RED "KO " RESET);
	}
}

void test_arena_strtrim_normal(void)
{
	t_arena arena;
	char *trim;
	char *str = "     This is my first C Library     ";
	char *set = " ";

	arena_build(&arena);
	trim = arena_strtrim(&arena, str, set);
	test_arena_print_check_strtrim(trim, "This is my first C Library");
	arena_destroy(&arena);
}

int main(void)
{
	test_arena_strtrim_normal();
	printf("\n");
}
