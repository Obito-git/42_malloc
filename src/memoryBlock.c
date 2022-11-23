//
// Created by Anton on 12/11/2022.
//
#include "allocator.h"

void *allocateBlock(void *heap, size_t size) {
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

static bool tryToExtendBlock(void *ptrHeader, void *nextHeader, size_t newSize) {
	if (ALLOC_SIZE(ptrHeader) > newSize) {
		size_t oldSize = ALLOC_SIZE(ptrHeader);
		ALLOC_SIZE(ptrHeader) = newSize;
		ALLOC_SIZE(NEXT_HEADER(ptrHeader)) = oldSize - newSize + ALLOC_SIZE(nextHeader);
		IS_ALLOC(NEXT_HEADER(ptrHeader)) = false;
		return true;
	}
	size_t currNextSize = ALLOC_SIZE(ptrHeader) + ALLOC_SIZE(nextHeader) + HEADER_SIZE;
	if (currNextSize == newSize) {
		ALLOC_SIZE(ptrHeader) = currNextSize;
		return true;
	}
	if (currNextSize - HEADER_SIZE > newSize) {
		ALLOC_SIZE(ptrHeader) = newSize;
		IS_ALLOC(nextHeader) = false;
		ALLOC_SIZE(NEXT_HEADER(ptrHeader)) = currNextSize - HEADER_SIZE - newSize;
		return true;
	}
	return false;
}

void *reallocBlock(void *ptr, void *heap, size_t newSize) {
	void *ptrHeader = ptr - HEADER_SIZE;
	void *nextHeader = NEXT_HEADER(ptrHeader);
	if (ALLOC_SIZE(ptrHeader) == newSize)
		return ptr;
	if (HEAP_GROUP(heap) != LARGE && !IS_ALLOC(nextHeader))
		if (tryToExtendBlock(ptrHeader, nextHeader, newSize))
			return ptr;
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

static void setDeallocBlocks(void *ptr, void **heap, void **prevBlock, void **currBlock) {
	*heap = findDeallocationRequiredHeap(ptr);
	if (*heap)
		*currBlock = FIRST_BLOCK(*heap);
	while (*heap && *currBlock < HEAP_END(*heap)) {
		if (BLOCK_CONTENT(*currBlock) == ptr)
			break;
		*prevBlock = *currBlock;
		*currBlock = NEXT_HEADER(*currBlock);
	}
	if (!*heap || *currBlock >= HEAP_END(*heap)) {
		ft_putstr("error for object 0x");
		ft_putunsigned_base(MEM_ADDRESS(ptr), HEX_BASE);
		ft_putendl(": pointer being free'd was not allocated");
	}
}

void deallocateBlock(void *ptr) {
	void *heap, *prevBlock, *currBlock;
	heap = prevBlock = currBlock = NULL;
	setDeallocBlocks(ptr, &heap, &prevBlock, &currBlock);
	if (!heap || currBlock >= HEAP_END(heap))
		return;
	HEAP_FREE_SIZE(heap) += ALLOC_SIZE(currBlock) + HEADER_SIZE;
	IS_ALLOC(currBlock) = false;
	HEAP_BLOCKS_COUNT(heap)--;
	if (HEAP_GROUP(heap) == LARGE || !HEAP_BLOCKS_COUNT(heap))
		deallocateHeap(heap);
	else if (prevBlock && !IS_ALLOC(prevBlock))
		mergeFreedBlocks(prevBlock, currBlock, heap);
	else if (!IS_ALLOC(NEXT_HEADER(currBlock)) && ALLOC_SIZE(NEXT_HEADER(currBlock)))
		mergeFreedBlocks(currBlock, NEXT_HEADER(currBlock), heap);
}
