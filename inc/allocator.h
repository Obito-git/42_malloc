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

#define TINY_ALLOC_SIZE 4 * getpagesize()
#define TINY_BLOCK_MAX_SIZE TINY_ALLOC_SIZE / 128
#define SMALL_ALLOC_SIZE 32 * getpagesize()
#define SMALL_BLOCK_MAX_SIZE SMALL_ALLOC_SIZE / 128
/*	Allocation macros */
#define HEADER_SIZE sizeof(t_header)
#define HEAP_HEADER_SIZE sizeof(t_heap)

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



//libft
char	*ft_strcpy(char *dest, const char *src);

#endif //MALLOC_ALLOCATOR_H
