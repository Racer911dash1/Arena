#include "arena.h"

static size_t arena_count_search_matches(const char *str, const char *search)
{
	char *ptr = strstr(str, search);
	size_t match_count = 0;

	if (ptr == NULL)
	{
		return (0);
	}
	while (ptr != NULL)
	{
		match_count += 1;
		ptr = strstr(ptr + 1, search);
	}
	return (match_count);
}

/**
 * Calculate the length of the new string by removing the matching words and adding their replacements instead.
 */
static size_t arena_new_strlen(const char *str, const char *search, const char *replace, size_t match_count)
{
	return (strlen(str) - (match_count * strlen(search)) + (match_count * strlen(replace)));
}

/**
 * A lot of pointer calculations.
 * We Want to keep track of two seperate sets of pointer positions. The start and
 * end of both `new_str` and `str`. Well we don't actually care about new_str's end pointer.
 * The index of the destination is handled with offset, which is then moved after a copy.
 * The end pointer then gets moved past the search word, which start copies,
 * after which end looks for the next point again.
 */
static void arena_replace_match(char *new_str, const char *str, const char *search, const char *replace)
{
	const size_t replacelen = strlen(replace);
	const size_t searchlen = strlen(search);
	const char *start = str;
	const char *end = strstr(start, search);
	size_t num;
	size_t offset = 0;

	while (end != NULL)
	{
		num = end - start;
		memcpy(new_str + offset, start, num);
		offset += num;
		memcpy(new_str + offset, replace, replacelen);
		offset += replacelen;
		end += searchlen;
		start = end;
		end = strstr(start, search);
	}
	memcpy(new_str + offset, start, strlen(start));
}

/**
 * If the search str is empty, then might aswell just use strdup instead.
 */
char *arena_strreplace(t_arena *arena, const char *str, const char *search, const char *replace)
{
	assert(arena != NULL && search != NULL && replace != NULL && "arena_strreplace cannot be NULL");

	char *new_str;
	size_t match_count;
	size_t new_str_len;

	if (*search == '\0')
	{
		return (arena_strdup(arena, str));
	}
	match_count = arena_count_search_matches(str, search);
	if (match_count == 0)
	{
		return (arena_strdup(arena, str));
	}
	new_str_len = arena_new_strlen(str, search, replace, match_count);
	new_str = arena_malloc(arena, (new_str_len + 1) * sizeof(char));
	if (new_str == NULL)
	{
		return (NULL);
	}
	arena_replace_match(new_str, str, search, replace);
	new_str[new_str_len] = '\0';
	return (new_str);
}
