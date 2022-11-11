#include "inc/allocator.h"

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

int main() {
	allocate();
	if (!memory)
		return (42);
	munmap(memory, SMALL_ALLOC_SIZE);
}
