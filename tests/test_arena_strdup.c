#include "arena.h"
#include "colors.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_arena_print_check_strdup(char *dup, char *compare)
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

void test_arena_strdup_simple(void)
{
	t_arena arena;
	char *dup;
	char *str = "Hello World";

	arena_build(&arena);
	dup = arena_strdup(&arena, str);
	test_arena_print_check_strdup(dup, "Hello World");
	arena_destroy(&arena);
}

void test_arena_strdup_empty(void)
{
	t_arena arena;
	char *dup;
	char *str = "";

	arena_build(&arena);
	dup = arena_strdup(&arena, str);
	test_arena_print_check_strdup(dup, "");
	arena_destroy(&arena);
}

void test_arena_strdup_single_char(void)
{
	t_arena arena;
	char *dup;
	char *str = "A";

	arena_build(&arena);
	dup = arena_strdup(&arena, str);
	test_arena_print_check_strdup(dup, "A");
	arena_destroy(&arena);
}

void test_arena_strdup_special_chars(void)
{
	t_arena arena;
	char *dup;
	char *str = "!@#$%^&*()";

	arena_build(&arena);
	dup = arena_strdup(&arena, str);
	test_arena_print_check_strdup(dup, "!@#$%^&*()");
	arena_destroy(&arena);
}

void test_arena_strdup_long_string(void)
{
	t_arena arena;
	char *dup;
	char *str = "This is a much longer string with multiple words and spaces to test duplication";

	arena_build(&arena);
	dup = arena_strdup(&arena, str);
	test_arena_print_check_strdup(dup, "This is a much longer string with multiple words and spaces to test duplication");
	arena_destroy(&arena);
}

int main(void)
{
	test_arena_strdup_simple();
	test_arena_strdup_empty();
	test_arena_strdup_single_char();
	test_arena_strdup_special_chars();
	test_arena_strdup_long_string();
	printf("\n");
}