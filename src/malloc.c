#include "allocator.h"

void *malloc(size_t size) {
	if (!size)
		return NULL;
	pthread_mutex_lock(&g_mutex);
	void *res = allocate(size);
	pthread_mutex_unlock(&g_mutex);
	return res;
}

void free(void *ptr) {
	if (!ptr)
		return;
	pthread_mutex_lock(&g_mutex);
	deallocateBlock(ptr);
	pthread_mutex_unlock(&g_mutex);
}

void *realloc(void *ptr, size_t size) {
	pthread_mutex_lock(&g_mutex);
	void *heap = findDeallocationRequiredHeap(ptr);
	if (!ptr) {
		pthread_mutex_unlock(&g_mutex);
		return malloc(size);
	}
	if (!heap) {
		ft_putstr("error for object 0x");
		ft_putunsigned_base(MEM_ADDRESS(ptr), HEX_BASE);
		ft_putendl(": pointer being realloc'd was not allocated");
		pthread_mutex_unlock(&g_mutex);
		return NULL;
	}
	if (!size) {
		pthread_mutex_unlock(&g_mutex);
		free(ptr);
		return NULL;
	}
	void *res = reallocBlock(ptr, heap, size);
	pthread_mutex_unlock(&g_mutex);
	return res;
}
