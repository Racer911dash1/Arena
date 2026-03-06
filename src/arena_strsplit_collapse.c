#include "arena.h"

/**
 * The first if condition only counts up when it's no longer on a delimiter,
 * even if the delimters are repeating.
 */
static size_t count_words(const char *str, const char *delimiter)
{
	size_t word_count = 0;
	bool is_word = false;

	for (size_t idx = 0; str[idx]; idx += 1)
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

/**
 * Counts the length of the word until strchr finds a delimiter or a null byte, after which
 * the length of the word has been determined.
 */
static size_t word_length(const char *str, const char *delimiter)
{
	size_t idx = 0;

	while (str[idx] && strchr(delimiter, str[idx]) == NULL)
	{
		idx += 1;
	}
	return (idx);
}

/**
 * Move the pointer of `str` if it's not on a delimiter.
 */
static void skip_delimiters(const char **str, const char *delimiter)
{
	while (**str && strchr(delimiter, **str))
	{
		*str += 1;
	}
}

/**
 * The main loop has a pattern of: find the next word -> copy word to array -> move pointer to the end of the copied word -> repeat.
 * Do that until all words have been copied.
 */
char **arena_strsplit_collapse(t_arena *arena, const char *str, const char *delimiter)
{
	assert(str != NULL && delimiter != NULL && "arena_strsplit_collapse cannot be NULL");

	size_t word_count = count_words(str, delimiter);
	size_t length;
	char **ptr = arena_malloc(arena, (word_count + 1) * sizeof(char *));

	if (ptr == NULL)
	{
		return (NULL);
	}
	for (size_t word = 0; word < word_count; word += 1)
	{
		skip_delimiters(&str, delimiter);
		length = word_length(str, delimiter);
		ptr[word] = arena_malloc(arena, (length + 1) * sizeof(char));
		if (ptr[word] == NULL)
		{
			return (NULL);
		}
		ptr[word][length] = '\0';
		memcpy(ptr[word], str, length);
		str += length;
	}
	ptr[word_count] = NULL;
	return (ptr);
}
