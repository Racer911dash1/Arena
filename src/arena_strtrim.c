#include "arena.h"

/**
 * @brief Trim the start and end of `str` matching `set`.
 *
 * If `set` contains all characters of `str`, and empty string will be returned.
 *
 * @retval Pointer to the trimmed string on success.
 * @retval `NULL` on malloc failure.
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
	trim = arena_calloc(arena, end - start + 1, sizeof(char));
	if (trim == NULL)
	{
		return (NULL);
	}
	return (memcpy(trim, str + start, end - start));
}
