NAME = a.out
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 -Iinc -Iminilib_ft/includes
SRCS_DIR = src/
SRCS = main.c allocator.c malloc.c memoryGroups.c heap.c memoryBlock.c print.c
LIBFT_PATH = minilib_ft/
LIBFT_NAME = libft.a
OBJ/OBJECTS		=	$(patsubst $(SRCS_DIR)%.c, obj/%.o, $(SRCS))
SRCS	:= $(foreach file,$(SRCS),$(SRCS_DIR)$(file))

all: $(NAME)
	
obj/%.o: $(SRCS_DIR)%.c Makefile | obj
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(LIBFT_NAME) $(OBJ/OBJECTS)
	$(CC) -o $(NAME) $^ $(CFLAGS) $(LIBFT_NAME)

$(LIBFT_NAME):
	$(MAKE) -C $(LIBFT_PATH) && cp -f $(LIBFT_PATH)/$(LIBFT_NAME) $(shell pwd)

obj:
	mkdir -p obj/utils

clean:
	$(MAKE) clean -C $(LIBFT_PATH)
	rm -f $(LIBFT_NAME)
	rm -rf obj
	rm -f .*.swp
	rm -rf $(NAME).dSYM

fclean: clean
	$(MAKE) fclean -C $(LIBFT_PATH)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
