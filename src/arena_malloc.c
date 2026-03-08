#include "arena.h"
#include <unistd.h>
#include <stdalign.h>
#include <stddef.h>
#include <stdlib.h>

/**
 * Get the system configuration for a page size, should always be a power of two.
 * Rounds `size` up  to the nearest multiple of the page size.
 */
static size_t arena_size_calculate(size_t size)
{
	const long page_size = sysconf(_SC_PAGESIZE);

	return ((size + page_size - 1) & ~(page_size - 1));
}

/**
 * Align the size to `max_align_t` to ensure proper starting addresses.
 */
static size_t arena_align_up(size_t size, size_t align)
{
	return ((size + align - 1) & ~(align - 1));
}

/**
 * Make a new node where the memory gets stored.
 * Since t_arena_node has a flexible array member we can immediately allocate
 * the approapriate size of the node.
 */
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
 * Align the requested size before determining how many bytes to allocate.
 * The else if statement checks if there's enough unused bytes in the allocated block.
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
