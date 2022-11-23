//
// Created by Anton on 11/11/2022.
//

#include "allocator.h"

t_heap *g_heap = NULL;

static rlim_t getAllocLimit(void) {
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
		correct_heap = g_heap = mmap(NULL, getHeapAllocSize(size), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
		initialiseNewHeap(g_heap, size);
	} else
		correct_heap = findAllocationRequiredHeap(size);
	if (!correct_heap)
		return NULL;
	return allocateBlock((void *) correct_heap, size);
}

void deallocateHeap(void *heap) {
	void *tmp = g_heap;
	if (heap == g_heap) {
		g_heap = g_heap->next;	
	} else {
		while (tmp && HEAP_NEXT(tmp) != heap)
			tmp = HEAP_NEXT(tmp);
		if (!tmp || !heap)
			return;
		HEAP_NEXT(tmp) = HEAP_NEXT(heap);
	}
	munmap(heap, HEAP_FREE_SIZE(heap) + HEADER_SIZE + HEAP_HEADER_SIZE);
}
