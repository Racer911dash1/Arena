#include "test_arena.h"

int test_arena_compare_substr(char *substr, char *compare)
{
	if (strcmp(substr, compare) == 0)
	{
		return (EXIT_SUCCESS);
	}
	else
	{
		return (EXIT_FAILURE);
	}
}

int test_arena_substr_simple()
{
	t_arena arena;
	int ret;
	char *substr;
	char *str = "Hello World";

	arena_build(&arena);
	substr = arena_substr(&arena, str, 6, 5);
	ret = test_arena_compare_substr(substr, "World");
	arena_destroy(&arena);
	return (ret);
}

int test_arena_substr_length_zero()
{
	t_arena arena;
	int ret;
	char *substr;
	char *str = "Hello World";

	arena_build(&arena);
	substr = arena_substr(&arena, str, 6, 5);
	ret = test_arena_compare_substr(substr, "World");
	arena_destroy(&arena);
	return (ret);
}

int test_arena_substr_start_larger_than_length_of_str()
{
	t_arena arena;
	int ret;
	char *substr;
	char *str = "Short";

	arena_build(&arena);
	substr = arena_substr(&arena, str, 10, 10);
	ret = test_arena_compare_substr(substr, "");
	arena_destroy(&arena);
	return (ret);
}

int test_arena_substr_empty_str()
{
	t_arena arena;
	int ret;
	char *substr;
	char *str = "";

	arena_build(&arena);
	substr = arena_substr(&arena, str, 0, 1);
	ret = test_arena_compare_substr(substr, "");
	arena_destroy(&arena);
	return (ret);
}

int main()
{
	RUN_TEST(test_arena_substr_simple);
	RUN_TEST(test_arena_substr_length_zero);
	RUN_TEST(test_arena_substr_start_larger_than_length_of_str);
	RUN_TEST(test_arena_substr_empty_str);
	printf("\n");
}