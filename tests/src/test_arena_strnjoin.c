#include "test_arena.h"

int test_arena_compare_strnjoin(char *join, char *compare)
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

int test_arena_strnjoin_simple()
{
	t_arena arena;
	int exit_status;
	size_t num = 5;
	char *join;
	char *str1 = "Hello";
	char *str2 = "World";

	arena_build(&arena);
	join = arena_strnjoin(&arena, str1, str2, num);
	exit_status = test_arena_compare_strnjoin(join, "HelloWorld");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strnjoin_num_longer_than_rightstr()
{
	t_arena arena;
	int exit_status;
	size_t num = 10;
	char *join;
	char *str1 = "Hello";
	char *str2 = "World";

	arena_build(&arena);
	join = arena_strnjoin(&arena, str1, str2, num);
	exit_status = test_arena_compare_strnjoin(join, "HelloWorld");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strnjoin_num_0()
{
	t_arena arena;
	int exit_status;
	size_t num = 0;
	char *join;
	char *str1 = "Hello";
	char *str2 = "World";

	arena_build(&arena);
	join = arena_strnjoin(&arena, str1, str2, num);
	exit_status = test_arena_compare_strnjoin(join, "Hello");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strnjoin_num_1()
{
	t_arena arena;
	int exit_status;
	size_t num = 1;
	char *join;
	char *str1 = "Hello";
	char *str2 = "World";

	arena_build(&arena);
	join = arena_strnjoin(&arena, str1, str2, num);
	exit_status = test_arena_compare_strnjoin(join, "HelloW");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strnjoin_num_shorter_than_rightstr()
{
	t_arena arena;
	int exit_status;
	size_t num = 3;
	char *join;
	char *str1 = "Hello";
	char *str2 = "World";

	arena_build(&arena);
	join = arena_strnjoin(&arena, str1, str2, num);
	exit_status = test_arena_compare_strnjoin(join, "HelloWor");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strnjoin_empty_leftstr_num_0()
{
	t_arena arena;
	int exit_status;
	size_t num = 0;
	char *join;
	char *str1 = "";
	char *str2 = "World";

	arena_build(&arena);
	join = arena_strnjoin(&arena, str1, str2, num);
	exit_status = test_arena_compare_strnjoin(join, "");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strnjoin_empty_leftstr_num_1()
{
	t_arena arena;
	int exit_status;
	size_t num = 1;
	char *join;
	char *str1 = "";
	char *str2 = "World";

	arena_build(&arena);
	join = arena_strnjoin(&arena, str1, str2, num);
	exit_status = test_arena_compare_strnjoin(join, "W");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strnjoin_empty_rightstr_num_0()
{
	t_arena arena;
	int exit_status;
	size_t num = 0;
	char *join;
	char *str1 = "Hello";
	char *str2 = "";

	arena_build(&arena);
	join = arena_strnjoin(&arena, str1, str2, num);
	exit_status = test_arena_compare_strnjoin(join, "Hello");
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_strnjoin_empty_rightstr_num_1()
{
	t_arena arena;
	int exit_status;
	size_t num = 1;
	char *join;
	char *str1 = "Hello";
	char *str2 = "";

	arena_build(&arena);
	join = arena_strnjoin(&arena, str1, str2, num);
	exit_status = test_arena_compare_strnjoin(join, "Hello");
	arena_destroy(&arena);
	return (exit_status);
}


int main()
{
	RUN_TEST(test_arena_strnjoin_simple);
	RUN_TEST(test_arena_strnjoin_num_longer_than_rightstr);
	RUN_TEST(test_arena_strnjoin_num_0);
	RUN_TEST(test_arena_strnjoin_num_1);
	RUN_TEST(test_arena_strnjoin_num_shorter_than_rightstr);
	RUN_TEST(test_arena_strnjoin_empty_leftstr_num_0);
	RUN_TEST(test_arena_strnjoin_empty_leftstr_num_1);
	RUN_TEST(test_arena_strnjoin_empty_rightstr_num_0);
	RUN_TEST(test_arena_strnjoin_empty_rightstr_num_1);
	printf("\n");
}