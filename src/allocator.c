#include "allocator.h"

t_heap *g_heap = NULL;
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void *allocate(size_t size) {
	if (!size)
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
    //2 times bcs it doesn't work instantly if called 1 time. can't find other solution
    //if (!g_heap)
    //    munmap(heap, HEAP_FREE_SIZE(heap) + HEADER_SIZE + HEAP_HEADER_SIZE);
}
