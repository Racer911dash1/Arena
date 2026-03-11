#include "test_arena.h"

int test_arena_print_check_strreplace(char *new_str, char *compare)
{
	if (strcmp(new_str, compare) == 0)
	{
		return (EXIT_SUCCESS);
	}
	else
	{
		return (EXIT_FAILURE);
	}
}

int test_arena_strreplace_simple()
{
	t_arena arena;
	int exit_status;
	char *str = "Hello World";
	char *search = "Hello";
	char *replace = "World";
	char *new_str;

	arena_build(&arena);
	new_str = arena_strreplace(&arena, str, search, replace);
	if (new_str == str)
	{
		arena_destroy(&arena);
		return (EXIT_FAILURE);
	}
	exit_status = test_arena_print_check_strreplace(new_str, "World World");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strreplace_empty_str()
{
	t_arena arena;
	int exit_status;
	char *str = "";
	char *search = "Hello";
	char *replace = "World";
	char *new_str;

	arena_build(&arena);
	new_str = arena_strreplace(&arena, str, search, replace);
	if (new_str == str)
	{
		arena_destroy(&arena);
		return (EXIT_FAILURE);
	}
	exit_status = test_arena_print_check_strreplace(new_str, "");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strreplace_empty_search()
{
	t_arena arena;
	int exit_status;
	char *str = "Hello World";
	char *search = "";
	char *replace = "World";
	char *new_str;

	arena_build(&arena);
	new_str = arena_strreplace(&arena, str, search, replace);
	if (new_str == str)
	{
		arena_destroy(&arena);
		return (EXIT_FAILURE);
	}
	exit_status = test_arena_print_check_strreplace(new_str, "Hello World");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strreplace_empty_replace()
{
	t_arena arena;
	int exit_status;
	char *str = "Hello World";
	char *search = "Hello";
	char *replace = "";
	char *new_str;

	arena_build(&arena);
	new_str = arena_strreplace(&arena, str, search, replace);
	if (new_str == str)
	{
		arena_destroy(&arena);
		return (EXIT_FAILURE);
	}
	exit_status = test_arena_print_check_strreplace(new_str, " World");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strreplace_search_longer_than_str()
{
	t_arena arena;
	int exit_status;
	char *str = "Long";
	char *search = "Longer";
	char *replace = "Longerest";
	char *new_str;

	arena_build(&arena);
	new_str = arena_strreplace(&arena, str, search, replace);
	if (new_str == str)
	{
		arena_destroy(&arena);
		return (EXIT_FAILURE);
	}
	exit_status = test_arena_print_check_strreplace(new_str, "Long");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strreplace_multiple_replacements()
{
	t_arena arena;
	int exit_status;
	char *str = "Every letter combination of er will be replaced with ER";
	char *search = "er";
	char *replace = "ER";
	char *new_str;

	arena_build(&arena);
	new_str = arena_strreplace(&arena, str, search, replace);
	if (new_str == str)
	{
		arena_destroy(&arena);
		return (EXIT_FAILURE);
	}
	exit_status = test_arena_print_check_strreplace(new_str, "EvERy lettER combination of ER will be replaced with ER");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strreplace_same_search_and_replace()
{
	t_arena arena;
	int exit_status;
	char *str = "Hello World";
	char *search = "Hello";
	char *replace = "Hello";
	char *new_str;

	arena_build(&arena);
	new_str = arena_strreplace(&arena, str, search, replace);
	if (new_str == str)
	{
		arena_destroy(&arena);
		return (EXIT_FAILURE);
	}
	exit_status = test_arena_print_check_strreplace(new_str, "Hello World");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strreplace_no_replacements()
{
	t_arena arena;
	int exit_status;
	char *str = "Hello World";
	char *search = "Unmatchable";
	char *replace = "World";
	char *new_str;

	arena_build(&arena);
	new_str = arena_strreplace(&arena, str, search, replace);
	if (new_str == str)
	{
		arena_destroy(&arena);
		return (EXIT_FAILURE);
	}
	exit_status = test_arena_print_check_strreplace(new_str, "Hello World");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strreplace_replace_at_start()
{
	t_arena arena;
	int exit_status;
	char *str = "123 456 789";
	char *search = "123";
	char *replace = "456 789";
	char *new_str;

	arena_build(&arena);
	new_str = arena_strreplace(&arena, str, search, replace);
	if (new_str == str)
	{
		arena_destroy(&arena);
		return (EXIT_FAILURE);
	}
	exit_status = test_arena_print_check_strreplace(new_str, "456 789 456 789");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strreplace_replace_at_middle()
{
	t_arena arena;
	int exit_status;
	char *str = "123 456 789";
	char *search = "456";
	char *replace = "789 123";
	char *new_str;

	arena_build(&arena);
	new_str = arena_strreplace(&arena, str, search, replace);
	if (new_str == str)
	{
		arena_destroy(&arena);
		return (EXIT_FAILURE);
	}
	exit_status = test_arena_print_check_strreplace(new_str, "123 789 123 789");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strreplace_replace_at_end()
{
	t_arena arena;
	int exit_status;
	char *str = "123 456 789";
	char *search = "789";
	char *replace = "123 456";
	char *new_str;

	arena_build(&arena);
	new_str = arena_strreplace(&arena, str, search, replace);
	if (new_str == str)
	{
		arena_destroy(&arena);
		return (EXIT_FAILURE);
	}
	exit_status = test_arena_print_check_strreplace(new_str, "123 456 123 456");
	arena_destroy(&arena);
	return (exit_status);
}

int main()
{
	RUN_TEST(test_arena_strreplace_simple);
	RUN_TEST(test_arena_strreplace_empty_str);
	RUN_TEST(test_arena_strreplace_empty_search);
	RUN_TEST(test_arena_strreplace_empty_replace);
	RUN_TEST(test_arena_strreplace_search_longer_than_str);
	RUN_TEST(test_arena_strreplace_multiple_replacements);
	RUN_TEST(test_arena_strreplace_same_search_and_replace);
	RUN_TEST(test_arena_strreplace_no_replacements);
	RUN_TEST(test_arena_strreplace_replace_at_start);
	RUN_TEST(test_arena_strreplace_replace_at_middle);
	RUN_TEST(test_arena_strreplace_replace_at_end);
	printf("\n");
}
