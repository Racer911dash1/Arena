#include "test_arena.h"

int test_arena_compare_strtrim(char *trim, char *compare)
{
	if (strcmp(trim, compare) == 0)
	{
		return (EXIT_SUCCESS);
	}
	else
	{
		return (EXIT_FAILURE);
	}
}

int test_arena_strtrim_normal()
{
	t_arena arena;
	int exit_status;
	char *trim;
	char *str = "     This is my first C Library     ";
	char *set = " ";

	arena_build(&arena);
	trim = arena_strtrim(&arena, str, set);
	exit_status = test_arena_compare_strtrim(trim, "This is my first C Library");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strtrim_no_padding()
{
	t_arena arena;
	int exit_status;
	char *trim;
	char *str = "NoSpaces";
	char *set = " ";

	arena_build(&arena);
	trim = arena_strtrim(&arena, str, set);
	exit_status = test_arena_compare_strtrim(trim, "NoSpaces");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strtrim_multiple_chars()
{
	t_arena arena;
	int exit_status;
	char *trim;
	char *str = "***---Hello World---***";
	char *set = "*-";

	arena_build(&arena);
	trim = arena_strtrim(&arena, str, set);
	exit_status = test_arena_compare_strtrim(trim, "Hello World");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strtrim_all_spaces()
{
	t_arena arena;
	int exit_status;
	char *trim;
	char *str = "     ";
	char *set = " ";

	arena_build(&arena);
	trim = arena_strtrim(&arena, str, set);
	exit_status = test_arena_compare_strtrim(trim, "");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strtrim_set_inbetween()
{
	t_arena arena;
	int exit_status;
	char *trim;
	char *str = "'   ,,,   '";
	char *set = " ,";

	arena_build(&arena);
	trim = arena_strtrim(&arena, str, set);
	exit_status = test_arena_compare_strtrim(trim, "'   ,,,   '");
	arena_destroy(&arena);
	return (exit_status);
}


int main()
{
	RUN_TEST(test_arena_strtrim_normal);
	RUN_TEST(test_arena_strtrim_no_padding);
	RUN_TEST(test_arena_strtrim_multiple_chars);
	RUN_TEST(test_arena_strtrim_all_spaces);
	RUN_TEST(test_arena_strtrim_set_inbetween);
	printf("\n");
}
