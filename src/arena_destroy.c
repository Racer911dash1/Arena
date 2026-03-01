#include "arena.h"

/**
 * @brief Free all allocated memory of `arena`
 *
 * This function should be called in the same scope that the variable is declared in.
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
