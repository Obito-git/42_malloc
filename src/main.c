#include "allocator.h"

/*
 *	void free(void *ptr);
 *	
 *	void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
 *	int munmap(void *addr, size_t len);
 *	int getpagesize(void);
 *	int getrlimit(int resource, struct rlimit *rlp);
 */

#include <stdio.h>
int main() {
	char *s1 = malloc(100);
	char *s2 = malloc(100);
	char *s3 = malloc(100);
	char *s4 = malloc(100);
	show_alloc_mem();

	free(s3);
	show_alloc_mem();
	s2 = realloc(s2, 15000);
	show_alloc_mem();
	
	(void) s1;
	(void) s2;
	(void) s3;
	(void) s4;
}