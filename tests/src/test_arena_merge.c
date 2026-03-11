#include "test_arena.h"

int test_arena_merge_leak()
{
	t_arena dest;
	t_arena src;
	size_t dest_count = 5;
	size_t src_count = 3;
	int exit_status = EXIT_SUCCESS;

	arena_build(&dest);
	arena_build(&src);
	for (size_t i = 0; i < dest_count; i += 1)
	{
		arena_malloc(&dest, sysconf(_SC_PAGESIZE));
	}
	for (size_t i = 0; i < src_count; i += 1)
	{
		arena_malloc(&src, sysconf(_SC_PAGESIZE));
	}
	arena_merge(&dest, &src);
	arena_destroy(&dest);
	return (exit_status);
}

int test_arena_merge_count_nodes()
{
	t_arena dest;
	t_arena src;
	t_arena_node *node;
	size_t dest_count = 5;
	size_t src_count = 3;
	size_t total_count = 0;
	int exit_status = EXIT_SUCCESS;

	arena_build(&dest);
	arena_build(&src);
	for (size_t i = 0; i < dest_count; i += 1)
	{
		arena_malloc(&dest, sysconf(_SC_PAGESIZE));
	}
	for (size_t i = 0; i < src_count; i += 1)
	{
		arena_malloc(&src, sysconf(_SC_PAGESIZE));
	}
	arena_merge(&dest, &src);
	node = dest.head;
	for (total_count = 0; node; total_count += 1)
	{
		node = node->next;
	}
	if (total_count != dest_count + src_count)
	{
		exit_status = EXIT_FAILURE;
	}
	arena_destroy(&dest);
	return (exit_status);
}

int test_arena_merge_empty_dest()
{
	t_arena dest;
	t_arena src;
	size_t dest_count = 0;
	size_t src_count = 3;
	int exit_status = EXIT_SUCCESS;

	arena_build(&dest);
	arena_build(&src);
	for (size_t i = 0; i < dest_count; i += 1)
	{
		arena_malloc(&dest, sysconf(_SC_PAGESIZE));
	}
	for (size_t i = 0; i < src_count; i += 1)
	{
		arena_malloc(&src, sysconf(_SC_PAGESIZE));
	}
	arena_merge(&dest, &src);
	arena_destroy(&dest);
	return (exit_status);
}

int test_arena_merge_empty_src()
{
	t_arena dest;
	t_arena src;
	size_t dest_count = 5;
	size_t src_count = 0;
	int exit_status = EXIT_SUCCESS;

	arena_build(&dest);
	arena_build(&src);
	for (size_t i = 0; i < dest_count; i += 1)
	{
		arena_malloc(&dest, sysconf(_SC_PAGESIZE));
	}
	for (size_t i = 0; i < src_count; i += 1)
	{
		arena_malloc(&src, sysconf(_SC_PAGESIZE));
	}
	arena_merge(&dest, &src);
	arena_destroy(&dest);
	return (exit_status);
}


int main()
{
	// Most tests will always give an OK, but may leak anyway.
	RUN_TEST(test_arena_merge_leak);
	RUN_TEST(test_arena_merge_count_nodes);
	RUN_TEST(test_arena_merge_empty_dest);
	RUN_TEST(test_arena_merge_empty_src);
	printf("\n");
}
