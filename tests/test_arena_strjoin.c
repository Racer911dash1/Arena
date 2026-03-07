#include "arena.h"
#include "colors.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_arena_print_check_strjoin(char *join, char *compare)
{
	if (strcmp(join, compare) == 0)
	{
		fprintf(stdout, GREEN "OK " RESET);
	}
	else
	{
		fprintf(stderr, RED "KO " RESET);
	}
}

void test_arena_strjoin_simple(void)
{
	t_arena arena;
	char *join;
	char *str1 = "Hello";
	char *str2 = "World";

	arena_build(&arena);
	join = arena_strjoin(&arena, str1, str2);
	test_arena_print_check_strjoin(join, "HelloWorld");
	arena_destroy(&arena);
}

void test_arena_strjoin_empty_leftstr()
{
	t_arena arena;
	char *join;
	char *str1 = "";
	char *str2 = "sentence in half";

	arena_build(&arena);
	join = arena_strjoin(&arena, str1, str2);
	test_arena_print_check_strjoin(join, "sentence in half");
	arena_destroy(&arena);
}

void test_arena_strjoin_empty_rightstr()
{
	t_arena arena;
	char *join;
	char *str1 = "I've sawed this";
	char *str2 = "";

	arena_build(&arena);
	join = arena_strjoin(&arena, str1, str2);
	test_arena_print_check_strjoin(join, "I've sawed this");
	arena_destroy(&arena);
}

void test_arena_strjoin_both_empty()
{
	t_arena arena;
	char *join;
	char *str1 = "";
	char *str2 = "";

	arena_build(&arena);
	join = arena_strjoin(&arena, str1, str2);
	test_arena_print_check_strjoin(join, "");
	arena_destroy(&arena);
}

void test_arena_strjoin_long()
{
	t_arena arena;
	char *join;
	char *str1 = "This is a very long string         ";
	char *str2 = "           with many empty spaces inbetween";

	arena_build(&arena);
	join = arena_strjoin(&arena, str1, str2);
	test_arena_print_check_strjoin(join, "This is a very long string                    with many empty spaces inbetween");
	arena_destroy(&arena);
}


int main(void)
{
	test_arena_strjoin_simple();
	test_arena_strjoin_empty_leftstr();
	test_arena_strjoin_empty_rightstr();
	test_arena_strjoin_both_empty();
	test_arena_strjoin_long();
	printf("\n");
}