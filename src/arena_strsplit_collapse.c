#include "arena.h"

static size_t count_words(const char *str, const char *delimiter)
{
	size_t word_count = 0;
	bool is_word = false;

	for (size_t idx = 0; str[idx]; idx++)
	{
		if (is_word == false && strchr(delimiter, str[idx]) == NULL)
		{
			word_count += 1;
			is_word = true;
		}
		if (strchr(delimiter, str[idx]))
		{
			is_word = false;
		}
	}
	return (word_count);
}

static size_t word_length(const char *str, const char *delimiter)
{
	size_t idx = 0;

	while (str[idx] && strchr(delimiter, str[idx]) == NULL)
	{
		idx += 1;
	}
	return (idx);
}

static void skip_delimiters(const char **str, const char *delimiter)
{
	while (**str && strchr(delimiter, **str))
	{
		*str += 1;
	}
}

/**
 * @brief Split `str` into multiple strings matching `delimiter`.
 *
 * Delimiters at the start and end of `str` will be omitted.
 * Repeating delimiters will be collapsed into a single delimiter.
 *
 * @retval Pointer to the split string on success.
 * @retval `NULL` on malloc failure.
 */
char **arena_strsplit_collapse(t_arena *arena, const char *str, const char *delimiter)
{
	assert(str != NULL && delimiter != NULL && "arena_strsplit_collapse cannot be NULL");

	size_t word_count = count_words(str, delimiter);
	size_t length;
	char **ptr = arena_calloc(arena, word_count + 1, sizeof(char *));

	if (ptr == NULL)
	{
		return (NULL);
	}
	for (size_t word = 0; word < word_count; word++)
	{
		skip_delimiters(&str, delimiter);
		length = word_length(str, delimiter);
		ptr[word] = arena_calloc(arena, length + 1, sizeof(char));
		if (ptr[word] == NULL)
		{
			return (NULL);
		}
		memcpy(ptr[word], str, length);
		str += length;
	}
	return (ptr);
}
