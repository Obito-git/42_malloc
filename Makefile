NAME = a.out
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 -Iinc
SRCS_DIR = src/
SRCS = main.c allocator.c malloc.c memoryGroups.c heap.c memoryBlock.c utils/ft_strcpy.c
OBJ/OBJECTS		=	$(patsubst $(SRCS_DIR)%.c, obj/%.o, $(SRCS))
SRCS	:= $(foreach file,$(SRCS),$(SRCS_DIR)$(file))

all: $(NAME)
	
obj/%.o: $(SRCS_DIR)%.c Makefile | obj
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ/OBJECTS)
	$(CC) -o $(NAME) $^ $(CFLAGS)

obj:
	mkdir -p obj/utils

clean:
	rm -rf obj
	rm -f .*.swp
	rm -rf $(NAME).dSYM

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
