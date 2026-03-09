#include "arena.h"

/**
 * Techincally we're counting delimiters here. But doing that easily determines
 * the amount of words to split.
 */
static size_t count_words(const char *str, const char *delimiter)
{
	size_t word_count = 1;

	for (size_t idx = 0; str[idx]; idx += 1)
	{
		if (strchr(delimiter, str[idx]))
		{
			word_count += 1;
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
 * Move the pointer of `str` until the end of the current word, then once more.
 * This is because it will guarantee that repeating delimiters will be accounted for.
 */
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
 * Regarding the main loop: Regardless whether `str` starts with a delimiter or
 * not, it will always be counted as a word. From there on the pointer gets
 * moved to the next delimiter and repeats the process.
 */
char **arena_strsplit_preserve(t_arena *arena, const char *str, const char *delimiter)
{
	assert(arena != NULL && str != NULL && delimiter != NULL && "arena_strsplit_preserve cannot be NULL");

	size_t word_count = count_words(str, delimiter);
	size_t length;
	char **ptr = arena_malloc(arena, (word_count + 1) * sizeof(char *));

	if (ptr == NULL)
	{
		return (NULL);
	}
	for (size_t word = 0; word < word_count; word += 1)
	{
		length = word_length(str, delimiter);
		ptr[word] = arena_malloc(arena, (length + 1) * sizeof(char));
		if (ptr[word] == NULL)
		{
			return (NULL);
		}
		ptr[word][length] = '\0';
		memcpy(ptr[word], str, length);
		next_word(&str, delimiter);
	}
	ptr[word_count] = NULL;
	return (ptr);
}
