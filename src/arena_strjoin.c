#include "arena.h"

/**
 * Unsure whether to add an if-check for empty strings or not.
 */
char *arena_strjoin(t_arena *arena, const char *leftstr, const char *rightstr)
{
	assert(leftstr != NULL && rightstr != NULL && "arena_strjoin cannot be NULL");

	const size_t leftstrlen = strlen(leftstr);
	const size_t rightstrlen = strlen(rightstr);
	char *joined = arena_malloc(arena, (leftstrlen + rightstrlen + 1) * sizeof(char));

	if (joined == NULL)
	{
		return (NULL);
	}
	memcpy(joined, leftstr, leftstrlen);
	memcpy(joined + leftstrlen, rightstr, rightstrlen);
	joined[leftstrlen + rightstrlen] = '\0';
	return (joined);
}