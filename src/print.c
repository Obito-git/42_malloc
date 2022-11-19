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
	ft_putunsigned_base(MEM_ADDRESS(heap), HEX_BASE);
	ft_putstr(", mem end: ");
	ft_putunsigned_base(MEM_ADDRESS(heap->end), HEX_BASE);
	ft_putstr(", blocks number: ");
	ft_putunsigned(heap->block_count);
	ft_putstr(", free mem: ");
	ft_putunsigned(HEAP_FREE_SIZE(heap));
	ft_putchar('\n');
}

static size_t show_heap_details(t_heap *heap) {
	size_t usedMemory = 0;
	size_t block_number = 1;
	void *tmp = ((char *) heap) + HEAP_HEADER_SIZE;
	while (tmp < heap->end) {
		ft_putstr("Block №");
		ft_putunsigned(block_number);
		ft_putstr(", is allocated: ");
		ft_putstr(IS_ALLOC(tmp) ? "Yes" : "No");
		ft_putstr(", block size: ");
		ft_putunsigned(ALLOC_SIZE(tmp));
		ft_putstr(", [0x");
		ft_putunsigned_base(MEM_ADDRESS(tmp + HEADER_SIZE), HEX_BASE);
		ft_putstr("] - [0x");
		ft_putunsigned_base(MEM_ADDRESS(NEXT_HEADER(tmp)), HEX_BASE);
		ft_putendl("]");
		if (IS_ALLOC(tmp))
			usedMemory += ALLOC_SIZE(tmp);
		block_number++;
		tmp = NEXT_HEADER(tmp);
	}
	ft_putstr("Total memory used ");
	ft_putunsigned(usedMemory);
	ft_putendl("");
	return usedMemory;
}

static void show_group_mem(t_group g) {
	t_heap *tmp = g_heap;
	size_t heap_number = 1;
	while (tmp) {
		if (tmp->group == g) {
			show_heap_header(tmp, heap_number);
			show_heap_details(tmp);
			heap_number++;
		}
		tmp = tmp->next;
	}
}

void show_alloc_mem() {
	if (!g_heap) {
		ft_putendl("No memory allocated");
		return;
	}
	show_group_mem(TINY);
	show_group_mem(SMALL);
	show_group_mem(LARGE);
}
