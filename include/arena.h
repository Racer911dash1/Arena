#ifndef ARENA_H
# define ARENA_H

# include <string.h>
# include <assert.h>

typedef struct s_arena_node t_arena_node;
typedef struct s_arena t_arena;

typedef struct s_arena_node
{
	t_arena_node *next; /**<Pointer to the next node.*/
	size_t offset; /**<Amount of bytes currently in use.*/
	size_t size; /**<Amount of useable bytes of the Node.*/
	unsigned char data[]; /**Flexible member array. Location of the stored bytes.*/
} t_arena_node;

typedef struct s_arena
{
	t_arena_node *head; /**<The head node of the linked list. Used to keep track of all pointers.*/
	t_arena_node *tail; /**<The tail end of the linked list. Used to quickly add another node.*/
} t_arena;

/**
 * @brief Initialize the arena to NULL.
 *
 * This function should be called first when declaring an arena variable.
 *
 * @param arena Pointer to the freshly declared arena.
 */
void arena_build(t_arena *arena);

/**
 * @brief Behaves similarly to standard calloc.
 *
 * If `num` or `size` are 0, a unique pointer value will be returned that can be
 * freed later.
 *
 * @param arena Stores the returning pointer.
 * @param num The number of members to allocate.
 * @param size The size of each `num`.
 *
 * @retval Pointer to the allocated memory, initialized to 0, on Success.
 * @retval NULL on malloc failure.
 */
void *arena_calloc(t_arena *arena, size_t num, size_t size);

/**
 * @brief Free all allocated memory.
 *
 * This function should be called when the arena is no longer needed.
 * Preferably only in the same scope as the declaration of the variable.
 *
 * @param arena The memory space pointed to by arena.
 */
void arena_destroy(t_arena *arena);

/**
 * @brief Return a line read from `fd`.
 *
 * Successive function calls will return successive lines.
 * Multiple file descriptors can be handled simultaneously.
 *
 * @param arena Stores the returning pointer.
 * @param fd The file descriptor to read from.
 *
 * @retval Pointer to the line read from `fd` on success.
 * @retval NULL on malloc failure or EOF.
 */
char *arena_getnextline(t_arena *arena, int fd);

/**
 * @brief Behaves similarly to standard malloc.
 *
 * If `size` is 0, a unique pointer value will be returned that can be freed later.
 *
 * @param arena Stores the returning pointer.
 * @param size Minimum amount of bytes to allocate.
 *
 * @retval Pointer to the allocated memory on Success.
 * @retval NULL on malloc failure.
 */
void *arena_malloc(t_arena *arena, size_t size);

/**
 * @brief Merge two different arenas together.
 *
 * Append `src` to `dest`, doing that will let `dest` be in full control of
 * all pointers while `src` will have its pointers be invalidated by setting
 * them to NULL.
 *
 * @param dest The arena to append to.
 * @param src The arena that will be discarded.
 */
void arena_merge(t_arena *dest, t_arena *src);

/**
 * @brief Duplicate a `str` to a new pointer.
 *
 * @param arena Stores the returning pointer.
 * @param str String to duplicate.
 *
 * @retval Pointer to a new string, which is a duplicate of `str`, on success.
 * @retval NULL on malloc failure.
 */
char *arena_strdup(t_arena *arena, const char *str);

/**
 * @brief Join two strings together into one.
 *
 * @param arena Stores the returning pointer.
 * @param leftstr The prefix of the new string.
 * @param rightstr The suffix of the new string.
 *
 * @retval Pointer from the result of both strings joined together on success.
 * @retval NULL on malloc failure.
 */
char *arena_strjoin(t_arena *arena, const char *leftstr, const char *rightstr);

/**
 * @brief Duplicate at most `num` bytes of `str` to a new pointer.
 *
 * If `num` is smaller than the length of `str`, only `num` bytes are copied,
 * with a null byte added at the end.
 * If `num` is larger than the length of `str`, then `num` will be clamped to the
 * length of `str`.
 *
 * @param arena Stores the returning pointer.
 * @param str String to duplicate.
 * @param num Amount of bytes to duplicate.
 *
 * @retval Pointer to a new string, which is a duplicate of `str`, on success.
 * @retval NULL on malloc failure.
 */
char *arena_strndup(t_arena *arena, const char *str, size_t num);

/**
 * @brief Join two strings together into one, with at most `num` bytes of `rightstr`
 * @brief appended to `leftstr`.
 *
 * @param arena Stores the returning pointer.
 * @param leftstr The prefix of the new string.
 * @param rightstr The suffix of the new string.
 * @param num The amount of bytes of `rightstr` to append.
 *
 * @retval Pointer from the result of both strings joined together on success.
 * @retval NULL on malloc failure.
 */
char *arena_strnjoin(t_arena *arena, const char *leftstr, const char *rightstr, size_t num);

/**
 * @brief Replace all instances of `search` with `replace`.
 *
 * If `search` is an empty string, or no matching words in `str` were found, then it is
 * the equivalent of calling arena_strdup(str).
 *
 * @param arena Stores the returning pointer.
 * @param str The string to replace the matching searches.
 * @param search The strings to be replaced.
 * @param replace The string to replace `search` with.
 *
 * @retval Pointer to the new string with replaced words on success.
 * @retval NULL on malloc failure.
 */
char *arena_strreplace(t_arena *arena, const char *str, const char *search, const char *replace);

/**
 * @brief Split `str` into multiple strings matching `delimiter`.
 *
 * Delimiters at the start and end of `str` will be omitted.
 * Repeating delimiters will be collapsed into a single delimiter.
 * Repeating characters in `delimiter` are ignored.
 *
 * @param arena Stores the returning pointer.
 * @param str The string to split.
 * @param delimiter A string of delimiters as the splitting point.
 *
 * @retval Pointer to the split string on success.
 * @retval NULL on malloc failure.
 */
char **arena_strsplit_collapse(t_arena *arena, const char *str, const char *delimiter);

/**
 * @brief Split `str` into multiple strings matching `delimiter`.
 *
 * Delimiters at the start and end of `str` will be treated as empty strings.
 * Repeating delimiters will be preserved and create empty strings as a result.
 * Repeating characters in `delimiter` are ignored.
 *
 * @param arena Stores the returning pointer.
 * @param str The string to split.
 * @param delimiter A string of delimiters as the splitting point.
 *
 * @retval Pointer to the split string on success.
 * @retval NULL on malloc failure.
 */
char **arena_strsplit_preserve(t_arena *arena, const char *str, const char *delimiter);

/**
 * @brief Trim the start and end of `str` matching `set`.
 *
 * If `set` contains all characters of `str`, an empty string will be returned.
 * Repeating characters in `set` are ignored.
 *
 * @param arena Stores the returning pointer.
 * @param str The string to trim.
 * @param set Set of characters to trim.
 *
 * @retval Pointer to the trimmed string on success.
 * @retval NULL on malloc failure.
 */
char *arena_strtrim(t_arena *arena, const char *str, const char *set);

/**
 * @brief Create a substring from `str` starting at `start` with at most `length` characters.
 *
 * An empty string will be returned if `start` is larger than the length of `str` or
 * length is 0.
 * The length of substring will be clamped up until the null byte of `str`.
 *
 * @param arena Stores the returning pointer.
 * @param str The string to create the substring from.
 * @param start The starting index to create the new string from.
 * @param length The length of the new string.
 *
 * @retval Pointer to the substring on success.
 * @retval NULL on malloc failure.
 */
char *arena_substr(t_arena *arena, const char *str, size_t start, size_t length);

#endif /* ARENA_H */
