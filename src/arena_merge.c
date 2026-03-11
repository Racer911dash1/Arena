#include "arena.h"

void arena_merge(t_arena *dest, t_arena *src)
{
	assert(dest != NULL && src != NULL && "arena_malloc cannot be NULL");

	if (dest->tail)
	{
		dest->tail->next = src->head;
	}
	else
	{
		dest->tail = src->head;
		dest->head = src->head;
	}
	src->head = NULL;
	src->tail = NULL;
}