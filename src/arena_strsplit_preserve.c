#include "arena.h"

static size_t count_words(const char *str, const char *delimiter)
{
	size_t word_count;
	size_t idx;

	word_count = 1;
	idx = 0;
	while (str[idx])
	{
		if (strchr(delimiter, str[idx]))
		{
			word_count += 1;
		}
		idx += 1;
	}
	return (word_count);
}

static size_t word_length(const char *str, const char *delimiter)
{
	size_t length = 0;

	while (str[length] && strchr(delimiter, str[length]) == NULL)
	{
		length += 1;
	}
	return (length);
}

static void next_word(const char **str, const char *delimiter)
{
	while (**str && strchr(delimiter, **str) == NULL)
	{
		*str += 1;
	}
	if (**str)
	{
		*str += 1;
	}
}

/**
 * @brief Split `str` into multiple strings matching `delimiter`.
 *
 * Delimiters at the start and end of `str` will be treated as empty strings.
 * Repeating delimiters will be preserved and create empty strings as a result.
 *
 * @retval Pointer to the split string on success.
 * @retval `NULL` on malloc failure.
 */
char **arena_strsplit_preserve(t_arena *arena, const char *str, const char *delimiter)
{
	assert(str != NULL && delimiter != NULL && "arena_strsplit_preserve cannot be NULL");

	size_t word_count = count_words(str, delimiter);
	size_t length;
	char **ptr = arena_calloc(arena, word_count + 1, sizeof(char *));

	if (ptr == NULL)
	{
		return (NULL);
	}
	for (size_t word = 0; word < word_count; word++)
	{
		length = word_length(str, delimiter);
		ptr[word] = arena_calloc(arena, length + 1, sizeof(char));
		if (ptr[word] == NULL)
		{
			return (NULL);
		}
		memcpy(ptr[word], str, length);
		next_word(&str, delimiter);
	}
	return (ptr);
}
