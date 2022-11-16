//
// Created by Anton on 12/11/2022.
//
#include "allocator.h"

void *allocateBlock(void *heap, size_t size) {
	if (!heap)
		return NULL;
	void *currentHeader = FIRST_BLOCK(heap);
	while (HEAP_BLOCKS_COUNT(heap)) {
		if (ALLOC_SIZE(currentHeader) >= size && !IS_ALLOC(currentHeader))
			break;
		currentHeader = NEXT_HEADER(currentHeader);
	}
	if (HEAP_GROUP(heap) != LARGE) {
		void *nextHeader = NEXT_HEADER(currentHeader);
		IS_ALLOC(nextHeader) = false;
		ALLOC_SIZE(nextHeader) = ALLOC_SIZE(currentHeader) - size - HEADER_SIZE;
	}
	ALLOC_SIZE(currentHeader) = size;
	IS_ALLOC(currentHeader) = true;
	HEAP_FREE_SIZE(heap) -= size + (HEAP_GROUP(heap) == LARGE ? 0 : (HEADER_SIZE));
	HEAP_BLOCKS_COUNT(heap)++;
	return (void *) ((char *) currentHeader + HEADER_SIZE);
}
