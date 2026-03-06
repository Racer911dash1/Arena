#include "arena.h"

char *arena_strdup(t_arena *arena, const char *str)
{
	assert(str != NULL && "arena_strdup cannot be NULL");

	const size_t len = strlen(str);
	char *ptr = arena_calloc(arena, len + 1, sizeof(char));

	if (ptr == NULL)
	{
		return (NULL);
	}
	return (memcpy(ptr, str, len));
}
