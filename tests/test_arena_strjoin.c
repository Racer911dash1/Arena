#include "test_arena.h"

int test_arena_compare_strjoin(char *join, char *compare)
{
	if (strcmp(join, compare) == 0)
	{
		return (EXIT_SUCCESS);
	}
	else
	{
		return (EXIT_FAILURE);
	}
}

int test_arena_strjoin_simple()
{
	t_arena arena;
	int ret;
	char *join;
	char *str1 = "Hello";
	char *str2 = "World";

	arena_build(&arena);
	join = arena_strjoin(&arena, str1, str2);
	ret = test_arena_compare_strjoin(join, "HelloWorld");
	arena_destroy(&arena);
	return (ret);
}

int test_arena_strjoin_empty_leftstr()
{
	t_arena arena;
	int ret;
	char *join;
	char *str1 = "";
	char *str2 = "sentence in half";

	arena_build(&arena);
	join = arena_strjoin(&arena, str1, str2);
	ret = test_arena_compare_strjoin(join, "sentence in half");
	arena_destroy(&arena);
	return (ret);
}

int test_arena_strjoin_empty_rightstr()
{
	t_arena arena;
	int ret;
	char *join;
	char *str1 = "I've sawed this";
	char *str2 = "";

	arena_build(&arena);
	join = arena_strjoin(&arena, str1, str2);
	ret = test_arena_compare_strjoin(join, "I've sawed this");
	arena_destroy(&arena);
	return (ret);
}

int test_arena_strjoin_both_empty()
{
	t_arena arena;
	int ret;
	char *join;
	char *str1 = "";
	char *str2 = "";

	arena_build(&arena);
	join = arena_strjoin(&arena, str1, str2);
	ret = test_arena_compare_strjoin(join, "");
	arena_destroy(&arena);
	return (ret);
}

int test_arena_strjoin_long()
{
	t_arena arena;
	int ret;
	char *join;
	char *str1 = "This is a very long string         ";
	char *str2 = "           with many empty spaces inbetween";

	arena_build(&arena);
	join = arena_strjoin(&arena, str1, str2);
	ret = test_arena_compare_strjoin(join, "This is a very long string                    with many empty spaces inbetween");
	arena_destroy(&arena);
	return (ret);
}


int main()
{
	RUN_TEST(test_arena_strjoin_simple);
	RUN_TEST(test_arena_strjoin_empty_leftstr);
	RUN_TEST(test_arena_strjoin_empty_rightstr);
	RUN_TEST(test_arena_strjoin_both_empty);
	RUN_TEST(test_arena_strjoin_long);
	printf("\n");
}