//
// Created by Anton on 11/11/2022.
//

#include "allocator.h"

t_heap *g_heap = NULL;

static rlim_t getAllocLimit(void)
{
	struct rlimit rpl;

	if (getrlimit(RLIMIT_DATA, &rpl) < 0)
		return (-1);
	return (rpl.rlim_max);
}

void *allocate(size_t size) {
	if (!size || size > getAllocLimit())
		return NULL;
	t_heap *correct_heap = NULL;
	if (!g_heap) {
		correct_heap = g_heap = mmap(NULL, getHeapSize(size), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
		initialiseNewHeap(g_heap, size);
	} else
		correct_heap = findRequiredHeap(size);
	return allocateBlock((void *) correct_heap, size);
}

void deallocate(void *ptr) {

	(void ) ptr;
}
