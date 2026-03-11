#include "arena.h"

char *arena_strnjoin(t_arena *arena, const char *leftstr, const char *rightstr, size_t num)
{
	assert(arena != NULL && leftstr != NULL && rightstr != NULL && "arena_strnjoin cannot be NULL");

	const size_t leftstrlen = strlen(leftstr);
	const size_t rightstrlen = strlen(rightstr);
	char *joined;

	if (num > rightstrlen)
	{
		num = rightstrlen;
	}
	joined = arena_malloc(arena, (leftstrlen + num + 1) * sizeof(char));
	if (joined == NULL)
	{
		return (NULL);
	}
	memcpy(joined, leftstr, leftstrlen);
	memcpy(joined + leftstrlen, rightstr, num);
	joined[leftstrlen + num] = '\0';
	return (joined);
}