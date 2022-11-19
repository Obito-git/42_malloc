//
// Created by Anton on 12/11/2022.
//
#include "allocator.h"

void *allocateBlock(void *heap, size_t size) {
	if (!heap)
		return NULL;
	void *currentHeader = FIRST_BLOCK(heap);
	while (HEAP_BLOCKS_COUNT(heap)) {
		size_t tmp = HEAP_BLOCKS_COUNT(heap); 
		(void) tmp;
		if (!IS_ALLOC(currentHeader) && (ALLOC_SIZE(currentHeader) > size + HEADER_SIZE || ALLOC_SIZE(currentHeader) == size))
			break;
		currentHeader = NEXT_HEADER(currentHeader);
	}
	if (HEAP_GROUP(heap) != LARGE && (ALLOC_SIZE(currentHeader)) != size) {
		void *nextHeader = currentHeader + size + HEADER_SIZE;
		IS_ALLOC(nextHeader) = false;
		ALLOC_SIZE(nextHeader) = ALLOC_SIZE(currentHeader) - size - HEADER_SIZE;
	}
	ALLOC_SIZE(currentHeader) = size;
	IS_ALLOC(currentHeader) = true;
	HEAP_FREE_SIZE(heap) -= size + (HEAP_GROUP(heap) == LARGE ? 0 : (HEADER_SIZE));
	HEAP_BLOCKS_COUNT(heap)++;
	return (void *) ((char *) currentHeader + HEADER_SIZE);
}

static void mergeFreedBlocks(void *prev, void *curr, void *heap) {
	if (prev >= curr)
		return;
	ALLOC_SIZE(prev) = ALLOC_SIZE(prev) + HEADER_SIZE + ALLOC_SIZE(curr);
	HEAP_BLOCKS_COUNT(heap)--;
	if (NEXT_HEADER(prev) < HEAP_END(heap) && !IS_ALLOC(NEXT_HEADER(prev))) {
		ALLOC_SIZE(prev) = ALLOC_SIZE(prev) + HEADER_SIZE + ALLOC_SIZE(NEXT_HEADER(prev));
		HEAP_BLOCKS_COUNT(heap)--;
	}
	if (!HEAP_BLOCKS_COUNT(heap))
		deallocateHeap(heap);
}

void deallocateBlock(void *ptr) {
	void *heap = findDeallocationRequiredHeap(ptr);
	void *prevBlock = NULL;
	void *currentBlock = NULL;
	if (heap)
		currentBlock = FIRST_BLOCK(heap);
	while (heap && currentBlock < HEAP_END(heap)) {
		if (BLOCK_CONTENT(currentBlock) == ptr)
			break;
		prevBlock = currentBlock;
		currentBlock = NEXT_HEADER(currentBlock);
	}
	if (!heap || currentBlock >= HEAP_END(heap)) {
		ft_putendl("pointer wasn't allocated");
		return ;
	}
	HEAP_FREE_SIZE(heap) += ALLOC_SIZE(currentBlock) + HEADER_SIZE;
	IS_ALLOC(currentBlock) = false;
	HEAP_BLOCKS_COUNT(heap)--;
	if (HEAP_GROUP(heap) == LARGE || !HEAP_BLOCKS_COUNT(heap))
		deallocateHeap(heap);
	else if (prevBlock && !IS_ALLOC(prevBlock))
		mergeFreedBlocks(prevBlock, currentBlock, heap);
	else if (!IS_ALLOC(NEXT_HEADER(currentBlock)) && ALLOC_SIZE(NEXT_HEADER(currentBlock)))
		mergeFreedBlocks(currentBlock,NEXT_HEADER(currentBlock), heap);
}
