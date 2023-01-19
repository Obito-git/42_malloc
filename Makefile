ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

# Lib
LIB_NAME = libft_malloc.so
LIB_FLAGS = -shared

#Variables
NAME = libft_malloc_$(HOSTTYPE).so
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 -Iinc -fpic
SRCS_DIR = src/
UTILS_DIR = minilib_ft/

SRCS =	allocator.c malloc.c memoryGroups.c heap.c memoryBlock.c print.c \
		$(UTILS_DIR)ft_putchar.c $(UTILS_DIR)ft_putstr.c $(UTILS_DIR)ft_putendl.c \
		$(UTILS_DIR)ft_putunsigned_base.c $(UTILS_DIR)ft_memcpy.c \
		$(UTILS_DIR)ft_putunsigned.c $(UTILS_DIR)ft_strlen.c $(UTILS_DIR)ft_putnbr.c
		
OBJ/OBJECTS		=	$(patsubst $(SRCS_DIR)%.c, obj/%.o, $(SRCS))
SRCS	:= $(foreach file,$(SRCS),$(SRCS_DIR)$(file))

#Rules
all: $(NAME)
	
obj/%.o: $(SRCS_DIR)%.c Makefile | obj
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ/OBJECTS)
	$(CC) -o $(NAME) $^ $(LIB_FLAGS)
	@rm -f $(LIB_NAME)
	ln -s $(NAME) $(LIB_NAME)

obj:
	mkdir -p obj/$(UTILS_DIR)

clean:
	rm -rf obj
	rm -f .*.swp

fclean: clean
	rm -f $(NAME) $(LIB_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
