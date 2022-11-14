//
// Created by Anton on 12/11/2022.
//
#include "allocator.h"

void *allocateBlock(void *heap, size_t size) {
	if (!heap)
		return NULL;
	t_heap *currentHeap = (t_heap *) heap;
	t_header *currentHeader = heap + HEAP_HEADER_SIZE;
	while (currentHeap->block_count) {
		if (currentHeader->size >= size && !currentHeader->allocated)
			break;
		currentHeader = (t_header *) ((char *) currentHeader + HEADER_SIZE + currentHeader->size);
	}
	if (currentHeap->group != LARGE) {
		t_header *nextHeader = (t_header *) ((char *) currentHeader + HEADER_SIZE + size);
		//printf("new block (%p) on %lu, next (%p) on %lu\n", currentHeader + HEADER_SIZE,
		//	   (char *) currentHeader - (char *) heap, nextHeader + HEADER_SIZE, (char *) nextHeader - (char *) heap);
		nextHeader->allocated = false;
		nextHeader->size = currentHeader->size - size - HEADER_SIZE;
	}
	currentHeader->size = size;
	currentHeader->allocated = true;
	currentHeap->free_size -= size + (currentHeap->group == LARGE ? 0 : (HEADER_SIZE));
	currentHeap->block_count++;
	//printf("Heap free: %lu, occupied %lu, total %lu\n", currentHeap->free_size, ((char *)nextHeader + BLOCK_SIZE) - (char *)heap,
	//	   currentHeap->free_size + ((char *)nextHeader + BLOCK_SIZE) - (char *)heap);
	return (void *) (currentHeader + HEADER_SIZE);
}
