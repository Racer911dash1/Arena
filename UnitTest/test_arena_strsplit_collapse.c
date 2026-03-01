#include "arena.h"
#include "colors.h"
#include <assert.h>
#include <stdio.h>

void test_arena_print_check_strsplit_collapse_null(char **split)
{
	if (split == NULL)
	{
		fprintf(stdout, GREEN "OK " RESET);
	}
	else
	{
		fprintf(stderr, RED "KO " RESET);
	}
}

void test_arena_print_check_strtrim(char **split, char **compare)
{
	size_t idx;
	for (idx = 0; compare[idx]; idx++)
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

void test_arena_strsplit_collapse_simple(void)
{
	t_arena arena;
	char **split;
	char *compare[] = {"Hello", "World", NULL};
	char *str = "Hello World";
	char *delimiters = " ";

	arena_build(&arena);
	split = arena_strsplit_collapse(&arena, str, delimiters);
	test_arena_print_check_strtrim(split, compare);
	arena_destroy(&arena);
}

void test_arena_strsplit_collapse_basic(void)
{
	t_arena arena;
	char **split;
	char *compare[] = {"This", "is", "my", "first", "C", "Library", NULL};
	char *str = " This is,,my   first.C Library,";
	char *delimiters = " ,.";

	arena_build(&arena);
	split = arena_strsplit_collapse(&arena, str, delimiters);
	test_arena_print_check_strtrim(split, compare);
	arena_destroy(&arena);
}

int main(void)
{
	test_arena_strsplit_collapse_simple();
	test_arena_strsplit_collapse_basic();
	printf("\n");
}
