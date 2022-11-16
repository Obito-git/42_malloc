//
// Created by Anton on 12/11/2022.
//
#include "allocator.h"

void initialiseNewHeap(void *memory, size_t blockSize) {
	if (!memory)
		return;
	t_heap *heap = (t_heap *) memory;
	heap->block_count = 0;
	heap->group = getBlockGroup(blockSize);
	heap->free_size = getHeapSize(blockSize) - HEAP_HEADER_SIZE - HEADER_SIZE;
	t_header *firstBlock = FIRST_BLOCK(memory);
	firstBlock->size = heap->free_size;
	firstBlock->allocated = false;
	heap->end = memory + getHeapSize(blockSize) - 1;
	printf("%p last\n", heap->end);
}

void *findRequiredHeap(size_t size) {
	t_group requiredGroup = getBlockGroup(size);
	t_heap *heaps = g_heap;
	while (heaps->next) {
		if (heaps->group == requiredGroup && heaps->free_size >= size + HEADER_SIZE)
			break;
		heaps = heaps->next;
	}
	if (heaps->group == requiredGroup && heaps->free_size >= size + HEADER_SIZE)
		return heaps;
	t_heap *new = mmap(NULL, getHeapSize(size), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	initialiseNewHeap(new, size);
	heaps->next = new;
	return new;
}
