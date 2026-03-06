#include "arena.h"

/**
 * Looping through the entire linked list and free each node, then setting
 * head and tail to NULL, allowing the same arena to be reused.
 */
void arena_destroy(t_arena *arena)
{
	assert(arena != NULL && "arena_destroy cannot be NULL");

	t_arena_node *node = arena->head;
	t_arena_node *next;

	while (node != NULL)
	{
		next = node->next;
		free(node);
		node = next;
	}
	arena->head = NULL;
	arena->tail = NULL;
}
