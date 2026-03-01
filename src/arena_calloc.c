#include "arena.h"

/**
 * @brief Similar to standard `calloc()`.
 */
void *arena_calloc(t_arena *arena, size_t num, size_t size)
{
	void *ptr;

	if (num == 0 || size == 0)
	{
		ptr = arena_malloc(arena, 1);
		return (memset(ptr, 0, 1));
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
