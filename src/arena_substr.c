#include "arena.h"

/**
 * The first if-check is basically a shortcut to return an empty string.
 * The second if-check clamps `length` to the maximum reasonable size for the substr to make.
 */
char *arena_substr(t_arena *arena, const char *str, size_t start, size_t length)
{
	assert(str != NULL && "arena_substr cannot be NULL");

	char *substr;
	size_t str_len = strlen(str);

	if (str_len == 0 || length == 0 || start > str_len)
	{
		return (arena_strdup(arena, ""));
	}
	if (start + length > str_len)
	{
		length = str_len - start;
	}
	substr = arena_malloc(arena, (length + 1) * sizeof(char));
	if (substr == NULL)
	{
		return (NULL);
	}
	substr[length] = '\0';
	return (memcpy(substr, str + start, length));
}