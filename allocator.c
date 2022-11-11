//
// Created by Anton on 11/11/2022.
//

#include "inc/allocator.h"

void allocate () {
	memory = mmap(NULL, SMALL_ALLOC_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0); //FIXME protection
}
