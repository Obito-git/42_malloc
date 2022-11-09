#include <stdio.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <sys/resource.h>
#include "libft/includes/libft.h"

/*
 *	void free(void *ptr);
 *	void *malloc(size_t size);
 *	void *realloc(void *ptr, size_t size);
 *	
 *	void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
 *	int munmap(void *addr, size_t len);
 *	int getpagesize(void);
 *	int getrlimit(int resource, struct rlimit *rlp);
 */

int main() {
	ft_printf("%d\n", 55);
}
