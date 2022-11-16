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

#include <stdio.h>
int main() {
	char *s1 = malloc(6);
	char *s2 = malloc(1);
	char *s3 = malloc(31);
	char *s4 = malloc(55);
	char *s5 = malloc(3);
	char *s6 = malloc(513);
	char *s7 = malloc(4097);
	(void) s1;
	(void) s2;
	(void) s3;
	(void) s4;
	(void) s5;
	(void) s6;
	(void) s7;
	/*
	for (int i = 0; i < 122; i++)
		malloc(512);
	malloc(503);
	malloc(1);
	 */
	show_alloc_mem();
}
