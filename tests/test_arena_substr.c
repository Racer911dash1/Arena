#include "arena.h"
#include "colors.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_arena_print_check_substr(char *substr, char *compare)
{
	if (strcmp(substr, compare) == 0)
	{
		fprintf(stdout, GREEN "OK " RESET);
	}
	else
	{
		fprintf(stderr, RED "KO " RESET);
	}
}

void test_arena_substr_simple(void)
{
	t_arena arena;
	char *substr;
	char *str = "Hello World";

	arena_build(&arena);
	substr = arena_substr(&arena, str, 6, 5);
	test_arena_print_check_substr(substr, "World");
	arena_destroy(&arena);
}

void test_arena_substr_length_zero()
{
	t_arena arena;
	char *substr;
	char *str = "Hello World";

	arena_build(&arena);
	substr = arena_substr(&arena, str, 6, 5);
	test_arena_print_check_substr(substr, "World");
	arena_destroy(&arena);
}

void test_arena_substr_start_larger_than_length_of_str()
{
	t_arena arena;
	char *substr;
	char *str = "Short";

	arena_build(&arena);
	substr = arena_substr(&arena, str, 10, 10);
	test_arena_print_check_substr(substr, "");
	arena_destroy(&arena);
}

void test_arena_substr_empty_str()
{
	t_arena arena;
	char *substr;
	char *str = "";

	arena_build(&arena);
	substr = arena_substr(&arena, str, 0, 1);
	test_arena_print_check_substr(substr, "");
	arena_destroy(&arena);
}

void test_arena_substr_clamp_length()
{
	t_arena arena;
	char *substr;
	char *str = "I only want the last word";

	arena_build(&arena);
	substr = arena_substr(&arena, str, 21, 15);
	if (strcmp(substr, "word") == 0 && substr[4] == '\0')
	{
		fprintf(stdout, GREEN "OK " RESET);
	}
	else
	{
		fprintf(stderr, RED "KO " RESET);
	}
	arena_destroy(&arena);
}


int main(void)
{
	test_arena_substr_simple();
	test_arena_substr_length_zero();
	test_arena_substr_start_larger_than_length_of_str();
	test_arena_substr_empty_str();
	test_arena_substr_clamp_length(); // Hard to confirm since if it works, out of bounds checking would theoretically happen.
	printf("\n");
}