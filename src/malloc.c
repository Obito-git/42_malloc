//
// Created by Anton on 11/11/2022.
//
#include "allocator.h"

void *malloc(size_t size) {
	if (!size)
		return NULL;
	return allocate(size);
}

void free(void *ptr) {
	if (!ptr)
		return;
	deallocateBlock(ptr);
}

void *realloc(void *ptr, size_t size) {
	void *heap = findDeallocationRequiredHeap(ptr);
	if (!ptr)
		return malloc(size);
	if (!heap) {
		ft_putstr("error for object 0x");
		ft_putunsigned_base(MEM_ADDRESS(ptr), HEX_BASE);
		ft_putendl(": pointer being realloc'd was not allocated");
		return NULL;
	}
	if (!size) {
		free(ptr);
		return NULL;
	}
	return reallocBlock(ptr, heap, size);
}