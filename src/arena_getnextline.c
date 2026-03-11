#include "arena.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

# define FILE_DESCRIPTOR_LIMIT 1024 // Arbitrary number. May change it when I know better ways than this.
# define GETNEXTLINE_BUFFER_SIZE 128 // Also an arbitrary number.

/**
 * Nothing special here. There won't be anything to trim when we're on the last line anyway.
 */
static char *arena_trim_leftover_line(t_arena *arena, char *buffer)
{
	char *ptr = NULL;
	char *line = NULL;
	size_t linelen = 0;
	size_t leftoverlen = 0;

	ptr = strchr(buffer, '\n');
	if (ptr == NULL)
	{
		return (NULL);
	}
	ptr += 1;
	linelen = ptr - buffer;
	leftoverlen = strlen(buffer) - linelen;
	line = arena_malloc(arena, (leftoverlen + 1) * sizeof(char));
	if (line == NULL)
	{
		return (NULL);
	}
	line[leftoverlen] = '\0';
	return (memcpy(line, ptr, leftoverlen));
}

/**
 * The if condition is needed incase we arrive at the last line, since it won't have a newline at the end.
 */
static char *arena_get_returning_line(t_arena *arena, const char *buffer)
{
	char *ptr = NULL;
	char *line = NULL;
	size_t linelen = 0;

	ptr = strchr(buffer, '\n');
	if (ptr)
	{
		ptr += 1;
		linelen = ptr - buffer;
	}
	else
	{
		linelen = strlen(buffer);
	}
	line = arena_malloc(arena, (linelen + 1) * sizeof(char));
	if (line == NULL)
	{
		return (NULL);
	}
	line[linelen] = '\0';
	return (memcpy(line, buffer, linelen));
}

/**
 * Read until a newline is found, if buffer is NULL then we duplicate the string first.
 */
static int arena_fill_buffer(t_arena *arena, char **buffer, int fd)
{
	ssize_t bytes_read;
	char line[GETNEXTLINE_BUFFER_SIZE + 1] = {0};

	while (*buffer == NULL || strchr(*buffer, '\n') == NULL)
	{
		bytes_read = read(fd, line, GETNEXTLINE_BUFFER_SIZE);
		if (bytes_read == -1)
		{
			return (EXIT_FAILURE);
		}
		if (bytes_read == 0)
		{
			break;
		}
		if (*buffer)
		{
			*buffer = arena_strnjoin(arena, *buffer, line, bytes_read);
		}
		else
		{
			*buffer = arena_strndup(arena, line, bytes_read);
		}
		if (*buffer == NULL)
		{
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

/**
 * Filling the buffer, and splitting the buffer in half where the first newline is found.
 * Newlines will not be truncated.
 */
char *arena_getnextline(t_arena *arena, int fd)
{
	assert(arena != NULL && "arena_getnextline cannot be NULL");

	static char *buffer[FILE_DESCRIPTOR_LIMIT];
	char *line;

	if (fd < 0 || fd >= FILE_DESCRIPTOR_LIMIT)
	{
		return (NULL);
	}
	if (arena_fill_buffer(arena, &buffer[fd], fd) == EXIT_FAILURE || buffer[fd] == NULL)
	{
		return (NULL);
	}
	line = arena_get_returning_line(arena, buffer[fd]);
	buffer[fd] = arena_trim_leftover_line(arena, buffer[fd]);
	return (line);
}