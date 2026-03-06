#include "arena.h"

/**
 * Moving through `str` one character at a time until no matching character is found.
 * Then the same is repeated from the end of `str`.
 */
char *arena_strtrim(t_arena *arena, char const *str, char const *set)
{
	assert(str != NULL && set != NULL && "arena_strtrim cannot be NULL");

	size_t start = 0;
	size_t end;
	char *trim;

	end = strlen(str);
	while (str[start] && strchr(set, str[start]))
	{
		start += 1;
	}
	if (start == end)
	{
		return (arena_calloc(arena, 1, sizeof(char)));
	}
	while (end > 0 && strchr(set, str[end - 1]))
	{
		end -= 1;
	}
	trim = arena_malloc(arena, end - (start + 1) * sizeof(char));
	if (trim == NULL)
	{
		return (NULL);
	}
	trim[end - start] = '\0';
	return (memcpy(trim, str + start, end - start));
}
