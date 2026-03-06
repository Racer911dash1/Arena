#include "arena.h"

/**
 * It's a necessary step to initialize the arena before its first use
 * as uninitialized values may segfault the program.
 */
void arena_build(t_arena *arena)
{
	assert(arena != NULL && "arena_build cannot be NULL");

	arena->head = NULL;
	arena->tail = NULL;
}
