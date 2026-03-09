#include "arena.h"

/**
 * Clamp `num` if `len` is smaller, prevents copying past the string.
 */
char *arena_strndup(t_arena *arena, const char *str, size_t num)
{
	assert(arena != NULL && str != NULL && "arena_strndup cannot be NULL");

	const size_t len = strlen(str);
	char *ptr;

	if (len < num)
	{
		num = len;
	}
	ptr = arena_malloc(arena, (num + 1) * sizeof(char));
	if (ptr == NULL)
	{
		return (NULL);
	}
	ptr[num] = '\0';
	return (memcpy(ptr, str, num));
}