#include "allocator.h"

/* @size is requested size of memory block */
size_t getHeapAllocSize(size_t size) {
	if (size > (size_t) SMALL_BLOCK_MAX_SIZE)
		return (size_t) (size + HEADER_SIZE + HEAP_HEADER_SIZE);
	if (size > (size_t) TINY_BLOCK_MAX_SIZE)
		return (size_t) SMALL_ALLOC_SIZE;
	return (size_t) TINY_ALLOC_SIZE;
}

t_group getBlockGroup(size_t size) {
	if (size > (size_t) SMALL_BLOCK_MAX_SIZE)
		return LARGE;
	if (size > (size_t) TINY_BLOCK_MAX_SIZE)
		return SMALL;
	return TINY;
}
