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
	char *s1 = malloc(500);
	char *s2 = malloc(4000);
	char *s3 = malloc(10000);
	show_alloc_mem();
	free(s2);
	printf("\n\n\n\n\n\n\n");
	show_alloc_mem();
	free(s3);
	printf("\n\n\n\n\n\n\n");
	show_alloc_mem();
	free(s1);
	printf("\n\n\n\n\n\n\n");
	show_alloc_mem();
	
	(void) s1;
	(void) s2;
	(void) s3;
}