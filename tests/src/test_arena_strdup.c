#include "test_arena.h"

int test_arena_compare_strdup(char *dup, char *compare)
{
	if (strcmp(dup, compare) == 0)
	{
		return (EXIT_SUCCESS);
	}
	else
	{
		return (EXIT_FAILURE);
	}
}

int test_arena_strdup_simple()
{
	t_arena arena;
	int exit_status;
	char *dup;
	char *str = "Hello World";

	arena_build(&arena);
	dup = arena_strdup(&arena, str);
	exit_status = test_arena_compare_strdup(dup, "Hello World");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strdup_empty()
{
	t_arena arena;
	int exit_status;
	char *dup;
	char *str = "";

	arena_build(&arena);
	dup = arena_strdup(&arena, str);
	exit_status = test_arena_compare_strdup(dup, "");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strdup_single_char()
{
	t_arena arena;
	int exit_status;
	char *dup;
	char *str = "A";

	arena_build(&arena);
	dup = arena_strdup(&arena, str);
	exit_status = test_arena_compare_strdup(dup, "A");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strdup_special_chars()
{
	t_arena arena;
	int exit_status;
	char *dup;
	char *str = "!@#$%^&*()";

	arena_build(&arena);
	dup = arena_strdup(&arena, str);
	exit_status = test_arena_compare_strdup(dup, "!@#$%^&*()");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strdup_long_string()
{
	t_arena arena;
	int exit_status;
	char *dup;
	char *str = "This is a much longer string with multiple words and spaces to test duplication";

	arena_build(&arena);
	dup = arena_strdup(&arena, str);
	exit_status = test_arena_compare_strdup(dup, "This is a much longer string with multiple words and spaces to test duplication");
	arena_destroy(&arena);
	return (exit_status);
}

int main()
{
	RUN_TEST(test_arena_strdup_simple);
	RUN_TEST(test_arena_strdup_empty);
	RUN_TEST(test_arena_strdup_single_char);
	RUN_TEST(test_arena_strdup_special_chars);
	RUN_TEST(test_arena_strdup_long_string);
	printf("\n");
}