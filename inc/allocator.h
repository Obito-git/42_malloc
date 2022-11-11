//
// Created by Anton on 11/11/2022.
//

#ifndef MALLOC_ALLOCATOR_H
#define MALLOC_ALLOCATOR_H
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>

#define TINY_ALLOC_SIZE 4 * getpagesize()
#define SMALL_ALLOC_SIZE 32 * getpagesize()
/*	Allocation macros */
#define BLOCK_SIZE sizeof(block_header)
#define HEADER_PTR(blockPayload) ((char *)(bp) - BLOCK_SIZE)
#define GET_SIZE(blockHeader) ((block_header *) (p))->size
#define IS_ALLOC(blockHeader) ((block_header *) (p))->allocated

typedef enum s_group {
	TINY, SMALL, LARGE
} t_group;

typedef struct s_heap {
	size_t			total_size;
	size_t 			free_size;
	size_t			block_count;
	t_group			group;
	struct s_heap		*next;
} t_heap;

typedef struct block_header {
	size_t	size;
	bool	allocated;
} block_header;

extern t_heap heap;
extern void *memory;

void allocate ();
void *malloc(size_t size);

#endif //MALLOC_ALLOCATOR_H
