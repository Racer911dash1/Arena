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

void test_arena_strtrim_no_padding(void)
{
	t_arena arena;
	char *trim;
	char *str = "NoSpaces";
	char *set = " ";

	arena_build(&arena);
	trim = arena_strtrim(&arena, str, set);
	test_arena_print_check_strtrim(trim, "NoSpaces");
	arena_destroy(&arena);
}

void test_arena_strtrim_multiple_chars(void)
{
	t_arena arena;
	char *trim;
	char *str = "***---Hello World---***";
	char *set = "*-";

	arena_build(&arena);
	trim = arena_strtrim(&arena, str, set);
	test_arena_print_check_strtrim(trim, "Hello World");
	arena_destroy(&arena);
}

void test_arena_strtrim_all_spaces(void)
{
	t_arena arena;
	char *trim;
	char *str = "     ";
	char *set = " ";

	arena_build(&arena);
	trim = arena_strtrim(&arena, str, set);
	test_arena_print_check_strtrim(trim, "");
	arena_destroy(&arena);
}

void test_arena_strtrim_null_byte()
{
	t_arena arena;
	char *trim;
	char *str = "Hi    ";
	char *set = " ";

	arena_build(&arena);
	trim = arena_strtrim(&arena, str, set);
	if (trim[2] == '\0')
	{
		fprintf(stdout, GREEN "OK " RESET);
	}
	else
	{
		fprintf(stderr, RED "KO " RESET);
	}
	arena_destroy(&arena);
}

void test_arena_strtrim_set_inbetween()
{
	t_arena arena;
	char *trim;
	char *str = "'   ,,,   '";
	char *set = " ,";

	arena_build(&arena);
	trim = arena_strtrim(&arena, str, set);
	test_arena_print_check_strtrim(trim, "'   ,,,   '");
	arena_destroy(&arena);
}


int main(void)
{
	test_arena_strtrim_normal();
	test_arena_strtrim_no_padding();
	test_arena_strtrim_multiple_chars();
	test_arena_strtrim_all_spaces();
	test_arena_strtrim_null_byte();
	test_arena_strtrim_set_inbetween();
	printf("\n");
}
