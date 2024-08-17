CC = gcc

NAME = minishell

HEADER_NAME = minishell.h

LIB_DIR = libft

LIBFT = libft.a

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -fsanitize=leak

HEADER_DIR = inc/

INCLUDES = -I $(HEADER_DIR)

LIB_READ = -lreadline

SRC = minishell.c \
		src/read_prompt.c\
		src/utils.c\
		src/utils2.c\
		src/parser.c\
		src/tokenize.c\
		src/tokenize_utils.c\
		src/env_manage.c\
		src/expander.c\
		src/expander_utils.c\
		src/maths.c\
		src/verify_tokens.c\
		src/sections.c\
		builtins/builtins.c\
		builtins/builtins_cd.c\
		builtins/builtins_env.c\
		builtins/builtins_export.c\

OBJS = src/$(SRC:.c=.o)

DEPS = src/$(SRC:.c=.d)

all:
	$(MAKE) -C $(LIB_DIR)
	$(MAKE) $(NAME)
	
$(NAME): $(OBJS) libft/$(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIB_READ) libft/$(LIBFT)

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
