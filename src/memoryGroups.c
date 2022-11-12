//
// Created by Anton on 12/11/2022.
//
#include "allocator.h"

size_t getHeapSize(size_t size) {
	if (size > (size_t) SMALL_BLOCK_MAX_SIZE)
		return (size_t) (size + HEADER_SIZE + HEAP_HEADER_SIZE);
	if (size > (size_t) TINY_BLOCK_MAX_SIZE)
		return (size_t) SMALL_ALLOC_SIZE;
	return (size_t) TINY_ALLOC_SIZE;
}

t_group getHeapGroup(size_t size) {
	if (size > (size_t) SMALL_ALLOC_SIZE)
		return LARGE;
	if (size > (size_t) TINY_ALLOC_SIZE)
		return SMALL;
	return TINY;
}

t_group getBlockGroup(size_t size) {
	if (size > (size_t) SMALL_BLOCK_MAX_SIZE)
		return LARGE;
	if (size > (size_t) TINY_BLOCK_MAX_SIZE)
		return SMALL;
	return TINY;
}