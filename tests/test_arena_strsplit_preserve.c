#include "test_arena.h"

int test_arena_compare_strsplit_preserve(char **split, char **compare)
{
	size_t idx;
	for (idx = 0; compare[idx]; idx += 1)
	{
		if (strcmp(split[idx], compare[idx]) != 0)
		{
			return (EXIT_FAILURE);
		}
	}
	if (split[idx] != NULL)
	{
		return (EXIT_FAILURE);
	}
	else
	{
		return (EXIT_SUCCESS);
	}
}

int test_arena_strsplit_preserve_simple()
{
	t_arena arena;
	int ret;
	char **split;
	char *compare[] = {"Hello", "World", NULL};
	char *str = "Hello World";
	char *delimiters = " ";

	arena_build(&arena);
	split = arena_strsplit_preserve(&arena, str, delimiters);
	ret = test_arena_compare_strsplit_preserve(split, compare);
	arena_destroy(&arena);
	return (ret);
}

int test_arena_strsplit_preserve_multiple()
{
	t_arena arena;
	int ret;
	char **split;
	char *compare[] = {"This", "is", "a", "test", NULL};
	char *str = "This is,a test";
	char *delimiters = " ,";

	arena_build(&arena);
	split = arena_strsplit_preserve(&arena, str, delimiters);
	ret = test_arena_compare_strsplit_preserve(split, compare);
	arena_destroy(&arena);
	return (ret);
}

int test_arena_strsplit_preserve_consecutive()
{
	t_arena arena;
	int ret;
	char **split;
	char *compare[] = {"Hello", "", "", "World", NULL};
	char *str = "Hello,,,World";
	char *delimiters = ",";

	arena_build(&arena);
	split = arena_strsplit_preserve(&arena, str, delimiters);
	ret = test_arena_compare_strsplit_preserve(split, compare);
	arena_destroy(&arena);
	return (ret);
}

int test_arena_strsplit_preserve_leading_delimiter()
{
	t_arena arena;
	int ret;
	char **split;
	char *compare[] = {"", "Hello", "World", NULL};
	char *str = ",Hello,World";
	char *delimiters = ",";

	arena_build(&arena);
	split = arena_strsplit_preserve(&arena, str, delimiters);
	ret = test_arena_compare_strsplit_preserve(split, compare);
	arena_destroy(&arena);
	return (ret);
}

int test_arena_strsplit_preserve_empty_string()
{
	t_arena arena;
	int ret;
	char **split;
	char *compare[] = {"", NULL};
	char *str = "";
	char *delimiters = " ";

	arena_build(&arena);
	split = arena_strsplit_preserve(&arena, str, delimiters);
	ret = test_arena_compare_strsplit_preserve(split, compare);
	arena_destroy(&arena);
	return (ret);
}

int test_arena_strsplit_preserve_no_delimiter()
{
	t_arena arena;
	int ret;
	char **split;
	char *compare[] = {":Hello World,how.are!you?doing;", NULL};
	char *str = ":Hello World,how.are!you?doing;";
	char *delimiters = "";

	arena_build(&arena);
	split = arena_strsplit_preserve(&arena, str, delimiters);
	ret = test_arena_compare_strsplit_preserve(split, compare);
	arena_destroy(&arena);
	return (ret);
}

int test_arena_strsplit_preserve_all_delimiter()
{
	t_arena arena;
	int ret;
	char **split;
	char *compare[] = {"", "", "", "", "", "", "", "", NULL};
	char *str = "abcdefg";
	char *delimiters = "abcdefg";

	arena_build(&arena);
	split = arena_strsplit_preserve(&arena, str, delimiters);
	ret = test_arena_compare_strsplit_preserve(split, compare);
	arena_destroy(&arena);
	return (ret);
}

int main()
{
	RUN_TEST(test_arena_strsplit_preserve_simple);
	RUN_TEST(test_arena_strsplit_preserve_multiple);
	RUN_TEST(test_arena_strsplit_preserve_consecutive);
	RUN_TEST(test_arena_strsplit_preserve_leading_delimiter);
	RUN_TEST(test_arena_strsplit_preserve_empty_string);
	RUN_TEST(test_arena_strsplit_preserve_no_delimiter);
	RUN_TEST(test_arena_strsplit_preserve_all_delimiter);
	printf("\n");
}