#include "test_arena.h"
#include <time.h>

int test_arena_ptr_not_null(char *ptr)
{
	if (ptr)
	{
		return (EXIT_SUCCESS);
	}
	else
	{
		return (EXIT_FAILURE);
	}
}

int test_arena_malloc_zero_bytes()
{
	t_arena arena;
	int ret;
	size_t size;
	char *ptr;

	arena_build(&arena);
	size = 0;
	ptr = arena_malloc(&arena, size);
	ret = test_arena_ptr_not_null(ptr);
	arena_destroy(&arena);
	return (ret);
}

int test_arena_malloc_one_byte()
{
	t_arena arena;
	int ret;
	size_t size;
	char *ptr;

	arena_build(&arena);
	size = 1;
	ptr = arena_malloc(&arena, size);
	ret = test_arena_ptr_not_null(ptr);
	arena_destroy(&arena);
	return (ret);
}

int test_arena_malloc_buffer_size_one()
{
	t_arena arena;
	int ret;
	size_t size;
	char *ptr;

	arena_build(&arena);
	size = sysconf(_SC_PAGESIZE);
	ptr = arena_malloc(&arena, size);
	ret = test_arena_ptr_not_null(ptr);
	arena_destroy(&arena);
	return (ret);
}

int test_arena_malloc_buffer_size_ten()
{
	t_arena arena;
	int ret;
	size_t size;
	char *ptr;

	arena_build(&arena);
	size = sysconf(_SC_PAGESIZE);
	for (size_t i = 0; i < 10; i += 1)
	{
		ptr = arena_malloc(&arena, size);
		ret = test_arena_ptr_not_null(ptr);
		if (ret == EXIT_FAILURE)
		{
			break;
		}
	}
	arena_destroy(&arena);
	return (ret);
}

int test_arena_malloc_buffer_size_plus_one_one()
{
	t_arena arena;
	int ret;
	size_t size;
	char *ptr;

	arena_build(&arena);
	size = sysconf(_SC_PAGESIZE) + 1;
	ptr = arena_malloc(&arena, size);
	ret = test_arena_ptr_not_null(ptr);
	arena_destroy(&arena);
	return (ret);
}

int test_arena_malloc_buffer_size_plus_one_ten()
{
	t_arena arena;
	int ret;
	size_t size;
	char *ptr;

	arena_build(&arena);
	size = sysconf(_SC_PAGESIZE) + 1;
	for (size_t i = 0; i < 10; i += 1)
	{
		ptr = arena_malloc(&arena, size);
		ret = test_arena_ptr_not_null(ptr);
		if (ret == EXIT_FAILURE)
		{
			break;
		}
	}
	arena_destroy(&arena);
	return (ret);
}

int test_arena_malloc_varying_sizes_ten()
{
	t_arena arena;
	int ret;
	size_t size;
	char *ptr;
	srand(time(NULL));

	arena_build(&arena);
	for (size_t i = 0; i < 10; i += 1)
	{
		size = rand() % sysconf(_SC_PAGESIZE) + 1;
		ptr = arena_malloc(&arena, size);
		ret = test_arena_ptr_not_null(ptr);
		if (ret == EXIT_FAILURE)
		{
			break;
		}
	}
	arena_destroy(&arena);
	return (ret);
}

int test_arena_malloc_pointer_comparison()
{
	t_arena arena;
	int ret;
	char *ptr1;
	char *ptr2;

	arena_build(&arena);
	ptr1 = arena_malloc(&arena, 4 * sizeof(char));
	ptr2 = arena_malloc(&arena, 4 * sizeof(char));
	if (ptr1 == ptr2)
	{
		ret = EXIT_FAILURE;
	}
	else
	{
		ret = EXIT_SUCCESS;
	}
	arena_destroy(&arena);
	return (ret);
}

int main()
{
	RUN_TEST(test_arena_malloc_zero_bytes);
	RUN_TEST(test_arena_malloc_one_byte);
	RUN_TEST(test_arena_malloc_buffer_size_one);
	RUN_TEST(test_arena_malloc_buffer_size_ten);
	RUN_TEST(test_arena_malloc_buffer_size_plus_one_one);
	RUN_TEST(test_arena_malloc_buffer_size_plus_one_ten);
	RUN_TEST(test_arena_malloc_varying_sizes_ten);
	RUN_TEST(test_arena_malloc_pointer_comparison);
	printf("\n");
}
