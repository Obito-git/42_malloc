#Lib
LIB_FLAGS = -L.. -lft_malloc
LIB_PATH = ..

#Variables
NAME = a.out
CC = gcc
CFLAGS = -g3 -I ../inc
SRCS_DIR = src/
SRCS = main.c
OBJ/OBJECTS		=	$(patsubst $(SRCS_DIR)%.c, obj/%.o, $(SRCS))
SRCS	:= $(foreach file,$(SRCS),$(SRCS_DIR)$(file))

all: $(NAME)
	
obj/%.o: $(SRCS_DIR)%.c Makefile | obj
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ/OBJECTS)
	@make -C $(LIB_PATH)
	$(CC) -o $(NAME) $^ $(CFLAGS) $(LIB_FLAGS) 

obj:
	mkdir -p obj/

clean:
	rm -rf obj
	rm -f .*.swp
	rm -rf $(NAME).dSYM

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus