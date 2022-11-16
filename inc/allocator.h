//
// Created by Anton on 11/11/2022.
//

#ifndef MALLOC_ALLOCATOR_H
#define MALLOC_ALLOCATOR_H
#include <sys/mman.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include "../minilib_ft/includes/libft.h"

#define TINY_ALLOC_SIZE 4 * getpagesize()
#define TINY_BLOCK_MAX_SIZE TINY_ALLOC_SIZE / 128
#define SMALL_ALLOC_SIZE 32 * getpagesize()
#define SMALL_BLOCK_MAX_SIZE SMALL_ALLOC_SIZE / 128
/*	Allocation macros */
#define HEADER_SIZE sizeof(t_header)
#define HEAP_HEADER_SIZE sizeof(t_heap)
/* Heap macros */
#define HEAP_GROUP(mem) (((t_heap *) mem)->group)
#define HEAP_BLOCKS_COUNT(mem) (((t_heap *) mem)->block_count)
#define HEAP_FREE_SIZE(mem) (((t_heap *) mem)->free_size)
/* Memory block macros */
#define IS_ALLOC(mem) (((t_header *) mem)->allocated)
#define ALLOC_SIZE(mem) (((t_header *) mem)->size)
#define NEXT_HEADER(mem) (((char *) mem) + HEADER_SIZE + ALLOC_SIZE(mem))
#define FIRST_BLOCK(mem) (t_header *) (mem + HEAP_HEADER_SIZE);


typedef enum s_group {
	TINY, SMALL, LARGE
} t_group;

typedef struct s_heap {
	//DEBUG
	size_t max_size;
	//NORMAL
	size_t 			free_size;
	size_t			block_count;
	t_group			group;
	void			*end;
	struct s_heap		*next;
} t_heap;

typedef struct block_header {
	size_t	size;
	bool	allocated;
} t_header;

extern t_heap *g_heap;

void *allocate(size_t size);
void *malloc(size_t size);

/*	Memory Groups */
size_t getHeapSize(size_t size);
t_group getHeapGroup(size_t size);
t_group getBlockGroup(size_t size);

/* Memory Block */
void *allocateBlock(void *heap, size_t size);
void initialiseNewHeap(void *memory, size_t blockSize);

/* Heap */
void *findRequiredHeap(size_t size);

/* Print */
void show_alloc_mem();



//libft
char	*ft_strcpy(char *dest, const char *src);

#endif //MALLOC_ALLOCATOR_H
