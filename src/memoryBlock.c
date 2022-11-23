//
// Created by Anton on 12/11/2022.
//
#include "allocator.h"

void *allocateBlock(void *heap, size_t size) {
	if (!heap)
		return NULL;
	void *currentHeader = FIRST_BLOCK(heap);
	while (HEAP_BLOCKS_COUNT(heap)) {
		if (!IS_ALLOC(currentHeader) &&
			(ALLOC_SIZE(currentHeader) > size + HEADER_SIZE || ALLOC_SIZE(currentHeader) == size))
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

void *reallocBlock(void *ptr, void *heap, size_t newSize) {
	void *ptrHeader = ptr - HEADER_SIZE;
	void *nextHeader = NEXT_HEADER(ptrHeader);
	if (ALLOC_SIZE(ptrHeader) == newSize)
		return ptr;
	if (HEAP_GROUP(heap) != LARGE && !IS_ALLOC(nextHeader)) {
		if (ALLOC_SIZE(ptrHeader) > newSize) {
			size_t oldSize = ALLOC_SIZE(ptrHeader);
			ALLOC_SIZE(ptrHeader) = newSize;
			ALLOC_SIZE(NEXT_HEADER(ptrHeader)) = oldSize - newSize + ALLOC_SIZE(nextHeader);
			IS_ALLOC(NEXT_HEADER(ptrHeader)) = false;
			return ptr;
		}
		size_t currNextSize = ALLOC_SIZE(ptrHeader) + ALLOC_SIZE(nextHeader) + HEADER_SIZE;
		if (currNextSize == newSize) {
			ALLOC_SIZE(ptrHeader) = currNextSize;
			return ptr;
		}
		if (currNextSize - HEADER_SIZE > newSize) {
			ALLOC_SIZE(ptrHeader) = newSize;
			IS_ALLOC(nextHeader) = false;
			ALLOC_SIZE(NEXT_HEADER(ptrHeader)) = currNextSize - HEADER_SIZE - newSize;
			return ptr;
		}
	}
	void *res = malloc(newSize);
	if (!res)
		return NULL;
	ft_memcpy(res, ptr, ALLOC_SIZE(ptrHeader) < newSize ? ALLOC_SIZE(ptrHeader) : newSize);
	free(ptr);
	return res;
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
		ft_putstr("error for object 0x");
		ft_putunsigned_base(MEM_ADDRESS(ptr), HEX_BASE);
		ft_putendl(": pointer being free'd was not allocated");
		return;
	}
	HEAP_FREE_SIZE(heap) += ALLOC_SIZE(currentBlock) + HEADER_SIZE;
	IS_ALLOC(currentBlock) = false;
	HEAP_BLOCKS_COUNT(heap)--;
	if (HEAP_GROUP(heap) == LARGE || !HEAP_BLOCKS_COUNT(heap))
		deallocateHeap(heap);
	else if (prevBlock && !IS_ALLOC(prevBlock))
		mergeFreedBlocks(prevBlock, currentBlock, heap);
	else if (!IS_ALLOC(NEXT_HEADER(currentBlock)) && ALLOC_SIZE(NEXT_HEADER(currentBlock)))
		mergeFreedBlocks(currentBlock, NEXT_HEADER(currentBlock), heap);
}
