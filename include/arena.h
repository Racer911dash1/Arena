#ifndef ARENA_H
# define ARENA_H

# include <stdlib.h>
# include <stddef.h>
# include <stdalign.h>
# include <stdbool.h>
# include <stdint.h>
# include <string.h>
# include <assert.h>

# ifndef ARENA_BUFFER_SIZE
#  define ARENA_BUFFER_SIZE 64
# endif

typedef struct s_arena_node	t_arena_node;
typedef struct s_arena		t_arena;

typedef struct s_arena_node
{
	t_arena_node	*next;
	size_t			offset;
	size_t			size;
	unsigned char	data[];
}	t_arena_node;

typedef struct s_arena
{
	t_arena_node	*head;
	t_arena_node	*tail;
}	t_arena;

void	arena_build(t_arena *arena);
void	*arena_malloc(t_arena *arena, size_t size);
void	*arena_calloc(t_arena *arena, size_t num, size_t size);
void	arena_destroy(t_arena *arena);

char	**arena_strsplit_collapse(t_arena *arena,
			const char *str, const char *delimiter);
char	**arena_strsplit_preserve(t_arena *arena,
			const char *str, const char *delimiter);

char	*arena_strdup(t_arena *arena, const char *str);
char	*arena_strndup(t_arena *arena, const char *str, size_t num);

char	*arena_strtrim(t_arena *arena, char const *str, char const *set);

#endif /* ARENA_H */
