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
	//char *s1 = malloc(6);
	//char *s2 = malloc(1);
	//char *s3 = malloc(31);
	//char *s4 = malloc(55);
	//char *s5 = malloc(3);
	char *s6 = malloc(513);
	char *s7 = malloc(4097);
	for (int i = 0; i < 123; i++)
		malloc(512);
	malloc(503);
	malloc(1);
	//ft_strcpy(s1, "Hello");
	//ft_strcpy(s2, "");
	//ft_strcpy(s3, "122222222222222222222222222223");
	//ft_strcpy(s4, "qwertyuiopasdfghjkl;zxcvbn1234567890987654321§```~gg~~");
	//ft_strcpy(s5, "gg");
	ft_strcpy(s6, "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus e");
	ft_strcpy(s7, "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. Nullam dictum felis eu pede mollis pretium. Integer tincidunt. Cras dapibus. Vivamus elementum semper nisi. Aenean vulputate eleifend tellus. Aenean leo ligula, porttitor eu, consequat vitae, eleifend ac, enim. Aliquam lorem ante, dapibus in, viverra quis, feugiat a, tellus. Phasellus viverra nulla ut metus varius laoreet. Quisque rutrum. Aenean imperdiet. Etiam ultricies nisi vel augue. Curabitur ullamcorper ultricies nisi. Nam eget dui. Etiam rhoncus. Maecenas tempus, tellus eget condimentum rhoncus, sem quam semper libero, sit amet adipiscing sem neque sed ipsum. Nam quam nunc, blandit vel, luctus pulvinar, hendrerit id, lorem. Maecenas nec odio et ante tincidunt tempus. Donec vitae sapien ut libero venenatis faucibus. Nullam quis ante. Etiam sit amet orci eget eros faucibus tincidunt. Duis leo. Sed fringilla mauris sit amet nibh. Donec sodales sagittis magna. Sed consequat, leo eget bibendum sodales, augue velit cursus nunc, quis gravida magna mi a libero. Fusce vulputate eleifend sapien. Vestibulum purus quam, scelerisque ut, mollis sed, nonummy id, metus. Nullam accumsan lorem in dui. Cras ultricies mi eu turpis hendrerit fringilla. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; In ac dui quis mi consectetuer lacinia. Nam pretium turpis et arcu. Duis arcu tortor, suscipit eget, imperdiet nec, imperdiet iaculis, ipsum. Sed aliquam ultrices mauris. Integer ante arcu, accumsan a, consectetuer eget, posuere ut, mauris. Praesent adipiscing. Phasellus ullamcorper ipsum rutrum nunc. Nunc nonummy metus. Vestibulum volutpat pretium libero. Cras id dui. Aenean ut eros et nisl sagittis vestibulum. Nullam nulla eros, ultricies sit amet, nonummy id, imperdiet feugiat, pede. Sed lectus. Donec mollis hendrerit risus. Phasellus nec sem in justo pellentesque facilisis. Etiam imperdiet imperdiet orci. Nunc nec neque. Phasellus leo dolor, tempus non, auctor et, hendrerit quis, nisi. Curabitur ligula sapien, tincidunt non, euismod vitae, posuere imperdiet, leo. Maecenas malesuada. Praesent congue erat at massa. Sed cursus turpis vitae tortor. Donec posuere vulputate arcu. Phasellus accumsan cursus velit. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Sed aliquam, nisi quis porttitor congue, elit erat euismod orci, ac placerat dolor lectus quis orci. Phasellus consectetuer vestibulum elit. Aenean tellus metus, bibendum sed, posuere ac, mattis non, nunc. Vestibulum fringilla pede sit amet augue. In turpis. Pellentesque posuere. Praesent turpis. Aenean posuere, tortor sed cursus feugiat, nunc augue blandit nunc, eu sollicitudin urna dolor sagittis lacus. Donec elit libero, sodales nec, volutpat a, suscipit non, turpis. Nullam sagittis. Suspendisse pulvinar, augue ac venenatis condimentum, sem libero volutpat nibh, nec pellentesque velit pede quis nunc. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Fusce id purus. Ut varius tincidunt libero. Phasellus dolor. Maecenas vestibulum mollis diam. Pellentesque ut neque. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. In dui magna, posuere eget, vestibulum et, tempor auctor, justo. In ac felis quis tortor malesuada pretium. Pellentesque auctor neque nec urna. Proin sapien ipsum, porta a, auctor quis, euismod ut, mi. Aenean viverra rhoncus pede. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Ut non enim eleifend felis pretium feugiat. Vivamus quis mi. Phasellus a est. Phasellus magna. In hac habitasse platea dictumst. Curabitur at lacus ac velit ornare lobortis. Cura");
	
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
			//printf("Block size: %lu, Is allocated: %s\n", current->size, current->allocated ? "YES" : "NO");
			char *s = (char *) (current + sizeof(t_header));
			(void) s;
			//printf("%lu: %p - %s\n", j, s, s);
				current = (t_header *)((char *)current + current->size + sizeof(t_header));
			j++;
		}
		tmp = tmp->next;
	}
}
