#ifndef MALLOC_ALLOCATOR_H
#define MALLOC_ALLOCATOR_H

#include <sys/mman.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <pthread.h>


/*	Allocation size*/
#define TINY_ALLOC_SIZE 4 * getpagesize()
#define TINY_BLOCK_MAX_SIZE TINY_ALLOC_SIZE / 128
#define SMALL_ALLOC_SIZE 32 * getpagesize()
#define SMALL_BLOCK_MAX_SIZE SMALL_ALLOC_SIZE / 128

/*	Allocation macros */
#define HEADER_SIZE sizeof(t_header)
#define HEAP_HEADER_SIZE sizeof(t_heap)

/*	Heap macros */
#define HEAP_GROUP(mem) (((t_heap *) mem)->group)
#define HEAP_BLOCKS_COUNT(mem) (((t_heap *) mem)->block_count)
#define HEAP_FREE_SIZE(mem) (((t_heap *) mem)->free_size)
#define HEAP_NEXT(mem) (((t_heap *) mem)->next)
#define HEAP_END(mem) (((t_heap *) mem)->end)

/*	Memory block macros */
#define IS_ALLOC(mem) (((t_header *) mem)->allocated)
#define ALLOC_SIZE(mem) (((t_header *) mem)->size)
#define BLOCK_CONTENT(mem) (mem + HEADER_SIZE)
#define NEXT_HEADER(mem) ((void *) (((char *) mem) + HEADER_SIZE + ALLOC_SIZE(mem)))
#define FIRST_BLOCK(mem) (t_header *) (mem + HEAP_HEADER_SIZE);

/*	Utils */
#define MEM_ADDRESS(mem) ((unsigned long) ((char *) mem))
#define HEX_BASE "0123456789abcdef"

typedef enum s_group {
	TINY, SMALL, LARGE
} t_group;

typedef struct s_heap {
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
extern pthread_mutex_t g_mutex;

/* To Impliment */
void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);

/*	Memory Groups */
size_t getHeapAllocSize(size_t size);
t_group getHeapGroup(size_t size);
t_group getBlockGroup(size_t size);

/* Memory Block */
void *allocateBlock(void *heap, size_t size);
void initialiseNewHeap(void *memory, size_t blockSize);
void *reallocBlock(void *ptr, void *heap, size_t newSize);
void deallocateBlock(void *ptr);

/* Heap */
void *allocate(size_t size);
void *findAllocationRequiredHeap(size_t size);
void *findDeallocationRequiredHeap(void *ptr);
void deallocateHeap(void *heap);
rlim_t getAllocLimit(void);

/* Print */
void show_alloc_mem();

/*	Libft */
void	ft_putendl(char *s);
void	ft_putstr(char *s);
void	ft_putchar(char c);
void	ft_putunsigned_base(unsigned long nbr, char *base);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_putunsigned(unsigned long n);
size_t	ft_strlen(const char *str);
void	ft_putnbr(long n);

#endif //MALLOC_ALLOCATOR_H
