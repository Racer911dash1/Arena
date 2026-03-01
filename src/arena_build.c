#include "arena.h"

/**
 * @brief Initialize the arena.
 *
 * This should be the first function to call.
 */
void arena_build(t_arena *arena)
{
	assert(arena != NULL && "arena_build cannot be NULL");

	arena->head = NULL;
	arena->tail = NULL;
}
