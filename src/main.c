#include "allocator.h"

/*
 *	void free(void *ptr);
 *	void *realloc(void *ptr, size_t size);
 *	
 *	void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
 *	int munmap(void *addr, size_t len);
 *	int getpagesize(void);
 *	int getrlimit(int resource, struct rlimit *rlp);
 */

void *memory = NULL;
#include <stdio.h>
int main() {
	char *s1 = malloc(6);
	char *s2 = malloc(1);
	char *s3 = malloc(31);
	char *s4 = malloc(55);
	char *s5 = malloc(3);
	char *s6 = malloc(513);
	ft_strcpy(s1, "Hello");
	ft_strcpy(s2, "");
	ft_strcpy(s3, "122222222222222222222222222223");
	ft_strcpy(s4, "qwertyuiopasdfghjkl;zxcvbn1234567890987654321§```~gg~~");
	ft_strcpy(s5, "gg");
	ft_strcpy(s6, "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus e");
	printf("%p #################\n", s6);
	
	t_heap *tmp = g_heap;
	size_t i = 1;
	

	printf("Global address start %p\n", g_heap);
	printf("Tiny block max_size %d, small block max_size %d\n", TINY_BLOCK_MAX_SIZE, SMALL_BLOCK_MAX_SIZE);
	printf("Sizeof t_heap %lu, sizeof t_header %lu\n", sizeof(t_heap), sizeof(t_header));
	printf("Tiny size 0-%d, Small %d-%d, Large %d-~\n", TINY_ALLOC_SIZE, TINY_ALLOC_SIZE, SMALL_ALLOC_SIZE, SMALL_ALLOC_SIZE);
	while (tmp) {
		printf("Heap №%li, Block count: %lu, Free size: %lu, Group: ", i, tmp->block_count, tmp->free_size);
		if (tmp->group == TINY)
			printf("TINY");
		else if (tmp->group == SMALL)
			printf("SMALL");
		else
			printf("LARGE");
		printf(", Max size: %lu\n", tmp->max_size);
		i++;
		printf("Blocks:\n");
		t_header *current = (t_header *) ((void *) tmp + sizeof(t_heap));
		size_t j = 0;
		while (j < tmp->block_count) {
			printf("Block size: %lu, Is allocated: %s\n", current->size, current->allocated ? "YES" : "NO");
			char *s = (char *) (current + sizeof(t_header));
			printf("%lu: %p - %s\n", j, s, s);
				current = (t_header *)((char *)current + current->size + sizeof(t_header));
			j++;
		}
		tmp = tmp->next;
	}
}
