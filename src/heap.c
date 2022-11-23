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
	heap->free_size = getHeapAllocSize(blockSize) - HEAP_HEADER_SIZE - HEADER_SIZE;
	t_header *firstBlock = FIRST_BLOCK(memory);
	firstBlock->size = heap->free_size;
	firstBlock->allocated = false;
	heap->end = memory + getHeapAllocSize(blockSize);
}

void *findAllocationRequiredHeap(size_t size) {
	t_group requiredGroup = getBlockGroup(size);
	t_heap *heaps = g_heap;
	while (true) {
		if (heaps->group == requiredGroup && heaps->free_size >= size + HEADER_SIZE) {
			void *currentHeader = FIRST_BLOCK((void *) heaps);
			while (currentHeader < heaps->end) {
				if (!IS_ALLOC(currentHeader) && (ALLOC_SIZE(currentHeader) > size + HEADER_SIZE || ALLOC_SIZE(currentHeader) == size))
					return heaps;
				currentHeader = NEXT_HEADER(currentHeader);
			}
		}
		if (!heaps->next)
			break;
		heaps = heaps->next;
	}
	t_heap *new = mmap(NULL, getHeapAllocSize(size), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	initialiseNewHeap(new, size);
	heaps->next = new;
	return new;
}

void *findDeallocationRequiredHeap(void *ptr) {
	if (!ptr)
		return NULL;
	void *tmp_glob = g_heap;
	while (tmp_glob) {
		if (ptr > tmp_glob && ptr < HEAP_END(tmp_glob))
			return tmp_glob;
		tmp_glob = HEAP_NEXT(tmp_glob);
	}
	return NULL;
}
