#include "test_arena.h"

int test_arena_strsplit_collapse_null(char **split)
{
	if (split == NULL)
	{
		return (EXIT_SUCCESS);
	}
	else
	{
		return (EXIT_FAILURE);
	}
}

int test_arena_compare_strtrim(char **split, char **compare)
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

int test_arena_strsplit_collapse_simple()
{
	t_arena arena;
	int exit_status;
	char **split;
	char *compare[] = {"Hello", "World", NULL};
	char *str = "Hello World";
	char *delimiters = " ";

	arena_build(&arena);
	split = arena_strsplit_collapse(&arena, str, delimiters);
	exit_status = test_arena_compare_strtrim(split, compare);
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strsplit_collapse_basic()
{
	t_arena arena;
	int exit_status;
	char **split;
	char *compare[] = {"This", "is", "my", "first", "C", "Library", NULL};
	char *str = " This is,,my   first.C Library,";
	char *delimiters = " ,.";

	arena_build(&arena);
	split = arena_strsplit_collapse(&arena, str, delimiters);
	exit_status = test_arena_compare_strtrim(split, compare);
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strsplit_collapse_empty_string()
{
	t_arena arena;
	int exit_status;
	char **split;
	char *compare[] = {NULL};
	char *str = "";
	char *delimiters = " ";

	arena_build(&arena);
	split = arena_strsplit_collapse(&arena, str, delimiters);
	exit_status = test_arena_compare_strtrim(split, compare);
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strsplit_collapse_only_delimiters()
{
	t_arena arena;
	int exit_status;
	char **split;
	char *compare[] = {NULL};
	char *str = "   ,,, ";
	char *delimiters = " ,";

	arena_build(&arena);
	split = arena_strsplit_collapse(&arena, str, delimiters);
	exit_status = test_arena_compare_strtrim(split, compare);
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strsplit_collapse_single_word()
{
	t_arena arena;
	int exit_status;
	char **split;
	char *compare[] = {"HelloWorld", NULL};
	char *str = "HelloWorld";
	char *delimiters = " ,";

	arena_build(&arena);
	split = arena_strsplit_collapse(&arena, str, delimiters);
	exit_status = test_arena_compare_strtrim(split, compare);
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strsplit_collapse_no_delimiter()
{
	t_arena arena;
	int exit_status;
	char **split;
	char *compare[] = {":Hello World,how.are!you?doing;", NULL};
	char *str = ":Hello World,how.are!you?doing;";
	char *delimiters = "";

	arena_build(&arena);
	split = arena_strsplit_collapse(&arena, str, delimiters);
	exit_status = test_arena_compare_strtrim(split, compare);
	arena_destroy(&arena);
	return (exit_status);
}

int main()
{
	RUN_TEST(test_arena_strsplit_collapse_simple);
	RUN_TEST(test_arena_strsplit_collapse_basic);
	RUN_TEST(test_arena_strsplit_collapse_empty_string);
	RUN_TEST(test_arena_strsplit_collapse_only_delimiters);
	RUN_TEST(test_arena_strsplit_collapse_single_word);
	RUN_TEST(test_arena_strsplit_collapse_no_delimiter);
	printf("\n");
}
