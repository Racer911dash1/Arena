#include "test_arena.h"
#include <time.h>

int test_arena_check_not_null(t_arena *arena)
{
	if (arena->head != NULL && arena->tail != NULL)
	{
		return (EXIT_SUCCESS);
	}
	else
	{
		return (EXIT_FAILURE);
	}
}

int test_arena_range_is_zero_bytes(char *ptr, size_t size)
{
	for (size_t i = 0; i < size; i += 1)
	{
		if (ptr[i] != '\0')
		{
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int test_arena_calloc_zero_bytes()
{
	t_arena arena;
	int exit_status;

	arena_build(&arena);
	arena_calloc(&arena, 0, 0);
	exit_status = test_arena_check_not_null(&arena);
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_calloc_one_byte()
{
	t_arena arena;
	int exit_status;
	size_t size;
	char *ptr;

	arena_build(&arena);
	size = 1;
	ptr = arena_calloc(&arena, 1, size);
	if (ptr == NULL)
	{
		return (EXIT_FAILURE);
	}
	exit_status = test_arena_range_is_zero_bytes(ptr, size);
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_calloc_buffer_size_one()
{
	t_arena arena;
	int exit_status;
	size_t size;
	char *ptr;

	arena_build(&arena);
	size = sysconf(_SC_PAGESIZE);
	ptr = arena_calloc(&arena, 1, size);
	if (ptr == NULL)
	{
		return (EXIT_FAILURE);
	}
	exit_status = test_arena_range_is_zero_bytes(ptr, size);
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_calloc_buffer_size_ten()
{
	t_arena arena;
	int exit_status;
	size_t size;
	char *ptr;

	arena_build(&arena);
	size = sysconf(_SC_PAGESIZE);
	for (size_t i = 0; i < 10; i += 1)
	{
		ptr = arena_calloc(&arena, 1, size);
		if (ptr == NULL)
		{
			exit_status = EXIT_FAILURE;
			break;
		}
		exit_status = test_arena_range_is_zero_bytes(ptr, size);
		if (exit_status == EXIT_FAILURE)
		{
			break;
		}
	}
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_calloc_buffer_size_plus_one_one()
{
	t_arena arena;
	int exit_status;
	size_t size;
	char *ptr;

	arena_build(&arena);
	size = sysconf(_SC_PAGESIZE) + 1;
	ptr = arena_calloc(&arena, 1, size);
	if (ptr == NULL)
	{
		return (EXIT_FAILURE);
	}
	exit_status = test_arena_range_is_zero_bytes(ptr, size);
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_calloc_buffer_size_plus_one_ten()
{
	t_arena arena;
	int exit_status;
	size_t size;
	char *ptr;

	arena_build(&arena);
	size = sysconf(_SC_PAGESIZE) + 1;
	for (size_t i = 0; i < 10; i += 1)
	{
		ptr = arena_calloc(&arena, 1, size);
		if (ptr == NULL)
		{
			exit_status = EXIT_FAILURE;
			break;
		}
		exit_status = test_arena_range_is_zero_bytes(ptr, size);
		if (exit_status == EXIT_FAILURE)
		{
			break;
		}
	}
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_calloc_varying_sizes_ten()
{
	t_arena arena;
	int exit_status;
	size_t size;
	char *ptr;
	srand(time(NULL));

	arena_build(&arena);
	for (size_t i = 0; i < 10; i += 1)
	{
		size = rand() % sysconf(_SC_PAGESIZE) + 1;
		ptr = arena_calloc(&arena, 1, size);
		if (ptr == NULL)
		{
			exit_status = EXIT_FAILURE;
			break;
		}
		exit_status = test_arena_range_is_zero_bytes(ptr, size);
		if (exit_status == EXIT_FAILURE)
		{
			break;
		}
	}
	arena_destroy(&arena);
	return (exit_status);
}

int main()
{
	RUN_TEST(test_arena_calloc_zero_bytes);
	RUN_TEST(test_arena_calloc_one_byte);
	RUN_TEST(test_arena_calloc_buffer_size_one);
	RUN_TEST(test_arena_calloc_buffer_size_ten);
	RUN_TEST(test_arena_calloc_buffer_size_plus_one_one);
	RUN_TEST(test_arena_calloc_buffer_size_plus_one_ten);
	RUN_TEST(test_arena_calloc_varying_sizes_ten);
	printf("\n");
}
