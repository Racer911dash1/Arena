#include "arena.h"
#include <stdint.h>

/**
 * The else if statement checks whether `num * size` will overflow.
 */
void *arena_calloc(t_arena *arena, size_t num, size_t size)
{
	void *ptr;

	if (num == 0 || size == 0)
	{
		return (arena_malloc(arena, 0));
	}
	else if (size > SIZE_MAX / num)
	{
		return (NULL);
	}
	ptr = arena_malloc(arena, num * size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	return (memset(ptr, 0, num * size));
}
