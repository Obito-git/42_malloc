NAME = a.out
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 -Iinc
SRCS_DIR = src/
UTILS_DIR = minilib_ft/
SRCS = main.c allocator.c malloc.c memoryGroups.c heap.c memoryBlock.c print.c \
	$(UTILS_DIR)ft_putchar.c $(UTILS_DIR)ft_putstr.c $(UTILS_DIR)ft_putendl.c $(UTILS_DIR)ft_putunsigned_base.c $(UTILS_DIR)ft_memcpy.c \
	$(UTILS_DIR)ft_putunsigned.c $(UTILS_DIR)ft_strlen.c
OBJ/OBJECTS		=	$(patsubst $(SRCS_DIR)%.c, obj/%.o, $(SRCS))
SRCS	:= $(foreach file,$(SRCS),$(SRCS_DIR)$(file))

all: $(NAME)
	
obj/%.o: $(SRCS_DIR)%.c Makefile | obj
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ/OBJECTS)
	$(CC) -o $(NAME) $^ $(CFLAGS)

obj:
	mkdir -p obj/$(UTILS_DIR)

clean:
	rm -rf obj
	rm -f .*.swp
	rm -rf $(NAME).dSYM

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
