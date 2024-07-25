CC = gcc

NAME = minishell

HEADER_NAME = minishell.h

LIB_DIR = libft

LIBFT = libft.a

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -fsanitize=leak

HEADER_DIR = inc/

INCLUDES = -I $(HEADER_DIR)

LIB_READ = -lreadline

SRC = 	minishell.c \
		env_manage.c \
		maths.c \
		builtins/builtins.c \
		builtins/builtins_env.c \
		builtins/builtins_export.c \
		builtins/builtins_cd.c \
		builtins/main_Emilie.c \
		utils.c

OBJS = src/$(SRC:.c=.o)

DEPS = src/$(SRC:.c=.d)

all:
	$(MAKE) -C $(LIB_DIR)
	$(MAKE) $(NAME)
	
$(NAME):	libft/$(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIB_READ) libft/$(LIBFT) -o $@ 

%.o: %.c Makefile libft/$(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

-include $(DEPS) 

clean:
	rm -f $(OBJS) $(DEPS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean r