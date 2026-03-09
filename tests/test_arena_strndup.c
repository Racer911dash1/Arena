#include "test_arena.h"

int test_arena_compare_strndup(char *dup, char *compare)
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

int test_arena_strndup_normal()
{
	t_arena arena;
	int ret;
	char *dup;
	char *str = "Hello World";

	arena_build(&arena);
	dup = arena_strndup(&arena, str, 5);
	ret = test_arena_compare_strndup(dup, "Hello");
	arena_destroy(&arena);
	return (ret);
}

int test_arena_strndup_exact_length()
{
	t_arena arena;
	int ret;
	char *dup;
	char *str = "Hello";

	arena_build(&arena);
	dup = arena_strndup(&arena, str, 5);
	ret = test_arena_compare_strndup(dup, "Hello");
	arena_destroy(&arena);
	return (ret);
}

int test_arena_strndup_longer_than_string()
{
	t_arena arena;
	int ret;
	char *dup;
	char *str = "Hi";

	arena_build(&arena);
	dup = arena_strndup(&arena, str, 100);
	ret = test_arena_compare_strndup(dup, "Hi");
	arena_destroy(&arena);
	return (ret);
}

int test_arena_strndup_zero_length()
{
	t_arena arena;
	int ret;
	char *dup;
	char *str = "Hello";

	arena_build(&arena);
	dup = arena_strndup(&arena, str, 0);
	ret = test_arena_compare_strndup(dup, "");
	arena_destroy(&arena);
	return (ret);
}

int test_arena_strndup_single_char()
{
	t_arena arena;
	int ret;
	char *dup;
	char *str = "Hello World";

	arena_build(&arena);
	dup = arena_strndup(&arena, str, 1);
	ret = test_arena_compare_strndup(dup, "H");
	arena_destroy(&arena);
	return (ret);
}

int main()
{
	RUN_TEST(test_arena_strndup_normal);
	RUN_TEST(test_arena_strndup_exact_length);
	RUN_TEST(test_arena_strndup_longer_than_string);
	RUN_TEST(test_arena_strndup_zero_length);
	RUN_TEST(test_arena_strndup_single_char);
	printf("\n");
}