#include "arena.h"

/**
 * @brief Similar to standard `strndup()`.
 */
char *arena_strndup(t_arena *arena, const char *str, size_t num)
{
	assert(str != NULL && "arena_strndup cannot be NULL");

	char *ptr = arena_calloc(arena, num + 1, sizeof(char));
	if (ptr == NULL)
	{
		return (NULL);
	}
	return (memcpy(ptr, str, num));
}