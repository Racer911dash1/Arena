#include "test_arena.h"
#include <fcntl.h>

int test_arena_getnextline_neg_1_fd()
{
	t_arena arena;
	char *line;
	int exit_status;

	arena_build(&arena);
	line = arena_getnextline(&arena, -1);
	if (line == NULL)
	{
		exit_status = EXIT_SUCCESS;
	}
	else
	{
		exit_status = EXIT_FAILURE;
	}
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_getnextline_1024_fd()
{
	t_arena arena;
	char *line;
	int exit_status;

	arena_build(&arena);
	line = arena_getnextline(&arena, 1024);
	if (line == NULL)
	{
		exit_status = EXIT_SUCCESS;
	}
	else
	{
		exit_status = EXIT_FAILURE;
	}
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_getnextline_1023_fd()
{
	t_arena arena;
	char *line;
	int exit_status;

	arena_build(&arena);
	line = arena_getnextline(&arena, 1023);
	if (line == NULL)
	{
		exit_status = EXIT_SUCCESS;
	}
	else
	{
		exit_status = EXIT_FAILURE;
	}
	arena_destroy(&arena);
	return (exit_status);
}

int test_arena_getnextline_empty()
{
	t_arena arena;
	char *line;
	int exit_status;
	int fd;

	arena_build(&arena);
	fd = open("tests/src/test_arena_getnextline_files/empty.txt", O_RDONLY);
	line = arena_getnextline(&arena, fd);
	if (line == NULL)
	{
		exit_status = EXIT_SUCCESS;
	}
	else
	{
		exit_status = EXIT_FAILURE;
	}
	arena_destroy(&arena);
	close(fd);
	return (exit_status);
}

int test_arena_getnextline_only_newlines()
{
	t_arena arena;
	char *line;
	int exit_status = EXIT_SUCCESS;
	int fd;
	size_t idx = 0;

	arena_build(&arena);
	fd = open("tests/src/test_arena_getnextline_files/only_newlines.txt", O_RDONLY);
	do
	{
		line = arena_getnextline(&arena, fd);
		if (line && *line != '\n' && idx != 20)
		{
			exit_status = EXIT_FAILURE;
		}
		idx += 1;
	} while (line);

	arena_destroy(&arena);
	close(fd);
	return (exit_status);
}

int test_arena_getnextline_basic()
{
	t_arena arena;
	char *line;
	int exit_status = EXIT_SUCCESS;
	int fd;

	arena_build(&arena);
	fd = open("tests/src/test_arena_getnextline_files/basic.txt", O_RDONLY);
	do
	{
		line = arena_getnextline(&arena, fd);
	} while (line);
	arena_destroy(&arena);
	close(fd);
	return (exit_status);
}

int test_arena_getnextline_one_line()
{
	t_arena arena;
	char *line;
	int exit_status = EXIT_SUCCESS;
	int fd;

	arena_build(&arena);
	fd = open("tests/src/test_arena_getnextline_files/one_line.txt", O_RDONLY);
	line = arena_getnextline(&arena, fd);
	if (strcmp(line, "According to all known laws of aviation, there is no way a bee should be able to fly.") != 0)
	{
		exit_status = EXIT_FAILURE;
	}
	line = arena_getnextline(&arena, fd);
	if (line != NULL)
	{
		exit_status = EXIT_FAILURE;
	}
	arena_destroy(&arena);
	close(fd);
	return (exit_status);
}

int test_arena_getnextline_bee_movie_script()
{
	t_arena arena;
	char *line;
	int exit_status = EXIT_SUCCESS;
	int fd;
	size_t idx = 0;

	arena_build(&arena);
	fd = open("tests/src/test_arena_getnextline_files/bee_movie_script.txt", O_RDONLY);
	do
	{
		line = arena_getnextline(&arena, fd);
		if (line == NULL && idx != 1364)
		{
			exit_status = EXIT_FAILURE;
		}
		idx += 1;
	} while (line);
	arena_destroy(&arena);
	close(fd);
	return (exit_status);
}

int test_arena_getnextline_one_char()
{
	t_arena arena;
	char *line;
	int exit_status = EXIT_SUCCESS;
	int fd;

	arena_build(&arena);
	fd = open("tests/src/test_arena_getnextline_files/one_char.txt", O_RDONLY);
	line = arena_getnextline(&arena, fd);
	if (strcmp(line, "a") != 0)
	{
		exit_status = EXIT_FAILURE;
	}
	line = arena_getnextline(&arena, fd);
	if (line != NULL)
	{
		exit_status = EXIT_FAILURE;
	}
	arena_destroy(&arena);
	close(fd);
	return (exit_status);
}

int main()
{
	RUN_TEST(test_arena_getnextline_neg_1_fd);
	RUN_TEST(test_arena_getnextline_1024_fd);
	RUN_TEST(test_arena_getnextline_1023_fd); // theoretically valid, but is hopefully a non-opened file descriptor at the time of testing.
	RUN_TEST(test_arena_getnextline_empty);
	RUN_TEST(test_arena_getnextline_only_newlines);
	RUN_TEST(test_arena_getnextline_basic);
	RUN_TEST(test_arena_getnextline_one_line);
	RUN_TEST(test_arena_getnextline_bee_movie_script);
	RUN_TEST(test_arena_getnextline_one_char);
	printf("\n");
}