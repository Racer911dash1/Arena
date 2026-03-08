#include "arena.h"
#include "colors.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void test_arena_print_check_strndup(char *dup, char *compare)
{
	if (strcmp(dup, compare) == 0)
	{
		fprintf(stdout, GREEN "OK " RESET);
	}
	else
	{
		fprintf(stderr, RED "KO " RESET);
	}
}

void test_arena_strndup_normal(void)
{
	t_arena arena;
	char *dup;
	char *str = "Hello World";

	arena_build(&arena);
	dup = arena_strndup(&arena, str, 5);
	test_arena_print_check_strndup(dup, "Hello");
	arena_destroy(&arena);
}

void test_arena_strndup_exact_length(void)
{
	t_arena arena;
	char *dup;
	char *str = "Hello";

	arena_build(&arena);
	dup = arena_strndup(&arena, str, 5);
	test_arena_print_check_strndup(dup, "Hello");
	arena_destroy(&arena);
}

void test_arena_strndup_longer_than_string(void)
{
	t_arena arena;
	char *dup;
	char *str = "Hi";

	arena_build(&arena);
	dup = arena_strndup(&arena, str, 100);
	test_arena_print_check_strndup(dup, "Hi");
	arena_destroy(&arena);
}

void test_arena_strndup_zero_length(void)
{
	t_arena arena;
	char *dup;
	char *str = "Hello";

	arena_build(&arena);
	dup = arena_strndup(&arena, str, 0);
	test_arena_print_check_strndup(dup, "");
	arena_destroy(&arena);
}

void test_arena_strndup_single_char(void)
{
	t_arena arena;
	char *dup;
	char *str = "Hello World";

	arena_build(&arena);
	dup = arena_strndup(&arena, str, 1);
	test_arena_print_check_strndup(dup, "H");
	arena_destroy(&arena);
}

int main(void)
{
	test_arena_strndup_normal();
	test_arena_strndup_exact_length();
	test_arena_strndup_longer_than_string();
	test_arena_strndup_zero_length();
	test_arena_strndup_single_char();
	printf("\n");
}