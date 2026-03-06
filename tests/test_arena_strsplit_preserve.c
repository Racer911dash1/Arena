#include "arena.h"
#include "colors.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_arena_print_check_strsplit_preserve(char **split, char **compare)
{
	size_t idx;
	for (idx = 0; compare[idx]; idx += 1)
	{
		if (strcmp(split[idx], compare[idx]) != 0)
		{
			fprintf(stderr, RED "KO " RESET);
			return ;
		}
	}
	if (split[idx] != NULL)
	{
		fprintf(stderr, RED "KO " RESET);
	}
	else
	{
		fprintf(stdout, GREEN "OK " RESET);
	}
}

void test_arena_strsplit_preserve_simple(void)
{
	t_arena arena;
	char **split;
	char *compare[] = {"Hello", "World", NULL};
	char *str = "Hello World";
	char *delimiters = " ";

	arena_build(&arena);
	split = arena_strsplit_preserve(&arena, str, delimiters);
	test_arena_print_check_strsplit_preserve(split, compare);
	arena_destroy(&arena);
}

void test_arena_strsplit_preserve_multiple(void)
{
	t_arena arena;
	char **split;
	char *compare[] = {"This", "is", "a", "test", NULL};
	char *str = "This is,a test";
	char *delimiters = " ,";

	arena_build(&arena);
	split = arena_strsplit_preserve(&arena, str, delimiters);
	test_arena_print_check_strsplit_preserve(split, compare);
	arena_destroy(&arena);
}

void test_arena_strsplit_preserve_consecutive(void)
{
	t_arena arena;
	char **split;
	char *compare[] = {"Hello", "", "", "World", NULL};
	char *str = "Hello,,,World";
	char *delimiters = ",";

	arena_build(&arena);
	split = arena_strsplit_preserve(&arena, str, delimiters);
	test_arena_print_check_strsplit_preserve(split, compare);
	arena_destroy(&arena);
}

void test_arena_strsplit_preserve_leading_delimiter(void)
{
	t_arena arena;
	char **split;
	char *compare[] = {"", "Hello", "World", NULL};
	char *str = ",Hello,World";
	char *delimiters = ",";

	arena_build(&arena);
	split = arena_strsplit_preserve(&arena, str, delimiters);
	test_arena_print_check_strsplit_preserve(split, compare);
	arena_destroy(&arena);
}

void test_arena_strsplit_preserve_empty_string(void)
{
	t_arena arena;
	char **split;
	char *compare[] = {"", NULL};
	char *str = "";
	char *delimiters = " ";

	arena_build(&arena);
	split = arena_strsplit_preserve(&arena, str, delimiters);
	test_arena_print_check_strsplit_preserve(split, compare);
	arena_destroy(&arena);
}

void test_arena_strsplit_preserve_no_delimiter(void)
{
	t_arena arena;
	char **split;
	char *compare[] = {":Hello World,how.are!you?doing;", NULL};
	char *str = ":Hello World,how.are!you?doing;";
	char *delimiters = "";

	arena_build(&arena);
	split = arena_strsplit_preserve(&arena, str, delimiters);
	test_arena_print_check_strsplit_preserve(split, compare);
	arena_destroy(&arena);
}

void test_arena_strsplit_preserve_all_delimiter(void)
{
	t_arena arena;
	char **split;
	char *compare[] = {"", "", "", "", "", "", "", "", NULL};
	char *str = "abcdefg";
	char *delimiters = "abcdefg";

	arena_build(&arena);
	split = arena_strsplit_preserve(&arena, str, delimiters);
	test_arena_print_check_strsplit_preserve(split, compare);
	arena_destroy(&arena);
}

int main(void)
{
	test_arena_strsplit_preserve_simple();
	test_arena_strsplit_preserve_multiple();
	test_arena_strsplit_preserve_consecutive();
	test_arena_strsplit_preserve_leading_delimiter();
	test_arena_strsplit_preserve_empty_string();
	test_arena_strsplit_preserve_no_delimiter();
	test_arena_strsplit_preserve_all_delimiter();
	printf("\n");
}