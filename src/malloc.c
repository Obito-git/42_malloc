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
	
}