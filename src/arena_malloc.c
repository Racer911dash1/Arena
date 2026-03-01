#include "arena.h"

/**
 * Round `size` up to the nearest multiple of `ARENA_BUFFER_SIZE`.
 *
 * Throws a compiler error if `ARENA_BUFFER_SIZE` is not a multiple of two.
 */
static size_t arena_size_calculate(size_t size)
{
	_Static_assert((ARENA_BUFFER_SIZE & (ARENA_BUFFER_SIZE - 1)) == 0,
		"ARENA_BUFFER_SIZE must be a power of two\n");
	return ((size + ARENA_BUFFER_SIZE - 1) & ~(ARENA_BUFFER_SIZE - 1));
}

/**
 * Align the size to `max_align_t` to ensure proper starting addresses.
 */
static size_t arena_align_up(size_t size, size_t align)
{
	return ((size + align - 1) & ~(align - 1));
}

static t_arena_node *arena_llist_new(size_t size)
{
	t_arena_node *node = malloc(sizeof(*node) + size);

	if (node == NULL)
	{
		return (NULL);
	}
	node->next = NULL;
	node->offset = 0;
	node->size = size;
	return (node);
}

/**
 * @brief Similar to standard `malloc()`.
 */
void *arena_malloc(t_arena *arena, size_t size)
{
	assert(arena != NULL && "arena_malloc cannot be NULL");

	const size_t aligned = arena_align_up(size, alignof(max_align_t));
	const size_t node_size = arena_size_calculate(aligned);
	t_arena_node *node;
	void *ptr = NULL;

	if (arena->tail == NULL)
	{
		node = arena_llist_new(node_size);
		if (node == NULL)
			return (NULL);
		arena->head = node;
		arena->tail = node;
	}
	else if (arena->tail->size - arena->tail->offset < aligned)
	{
		node = arena_llist_new(node_size);
		if (node == NULL)
			return (NULL);
		arena->tail->next = node;
		arena->tail = node;
	}
	ptr = arena->tail->data + arena->tail->offset;
	arena->tail->offset += aligned;
	return (ptr);
}
