//
// Created by Anton on 15/11/2022.
//
#include "allocator.h"

static void show_heap_header(t_heap *heap, size_t heap_number) {
	ft_putstr("Heap №");
	ft_putunsigned(heap_number);
	ft_putstr(", size: ");
	if (heap->group == TINY)
		ft_putstr("TINY");
	else if (heap->group == SMALL)
		ft_putstr("SMALL");
	else
		ft_putstr("LARGE");
	ft_putstr(", mem start: 0x");
	ft_putunsigned_base((unsigned long) ((char *) heap), "0123456789abcdef");
	ft_putstr(", mem end: ");
	ft_putunsigned_base((unsigned long) ((char *) heap->end), "0123456789abcdef");
	ft_putstr(", blocks number: ");
	ft_putunsigned(heap->block_count);
	ft_putchar('\n');
}

static size_t show_heap_details(t_heap *heap) {
	size_t usedMemory = 0;
	void *tmp = ((char *) heap) + HEAP_HEADER_SIZE;
	while (tmp < heap->end) {
		if (IS_ALLOC(tmp))
			printf("@@@@@@@@@@@\n");
		tmp = NEXT_HEADER(tmp);
	}
	(void) usedMemory;
	return 1;
}

static size_t show_tiny_mem() {
	t_heap *tmp = g_heap;
	size_t heap_number = 1;
	while (tmp) {
		if (tmp->group == TINY) {
			show_heap_header(tmp, heap_number);
			show_heap_details(tmp);
			heap_number++;
		}
		tmp = tmp->next;
	}
	return 2;
}

void show_alloc_mem() {
	show_tiny_mem();
	(void) 1;
		
}
