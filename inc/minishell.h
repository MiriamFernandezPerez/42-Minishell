/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:05:00 by mirifern          #+#    #+#             */
/*   Updated: 2024/07/10 19:23:04 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# include <string.h>

# define NO_ARGS "Error. Execution don't allow arguments\n"
# define NO_GETCWD "getcwd() error, can't read current path directory\n"
# define EXIT "exit\n"
# define ERR_SQUOTE "dquote>\nError while looking for matching `''\n"
# define ERR_DQUOTE "dquote>\nError while looking for matching `\"\'\n"
# define ERR_PIPE "bash: syntax error near unexpected token `|'\n"

# define MAX_TOKENS 100
# define TOKEN_SIZE 64

//delimiters
# define CMD 0//Command
# define SPACES 1 //Spaces and tabs
# define PIPE 2 // |
# define INPUT 3 // <
# define TRUNC 4 // >
# define SQUOTE 5 // '
# define DQUOTE 6 // "
# define HEREDOC 7 // <<
# define APPEND 8 // >>
# define END 9
# define ARG 10 // string or argument

/*
typedef struct s_??????
{
	char	**cmd;
	char	*infile;
	char	*outfile;
	char	
	t_tokens	*previous;
	t_tokens	*next;
}			t_??????;*/

typedef struct s_tokens
{
	char	*value;
	int		type;
}			t_tokens;

typedef struct s_data
{
	char		*prompt;
	int			tokens_qt;
	t_tokens	**tokens;
}			t_data;

//Main minishell.c
int		ft_initialize(t_data **data);
int		main(int ac, char **av, char **env);

//read_prompt.c
int		only_spaces(char *s);
int		ft_read_prompt(t_data *data);

//parse.c
int		end_quote(char *input, char c, int i);
int		find_pipes(char *input);
int		find_pair_quote(char *input, int *i, char quote_type);
int		find_quotes(char *input, int squote, int dquote);
int		ft_parser(char *input);

//tokenize.c
void	tok_delimiter(t_data *data, char *input, int *ind, int *start);
char	*tok_nodelimiter(t_data *data, int *ind, int *start, int *end);
void	define_delimiter(t_data *data, int *start, int *end, int *index);
void	ft_tokenizer(t_data *d, int len, int start, int index);

//tokenize_utils.c
void	remove_quotes(char *str);
void	clean_tokens(t_data *d);
void	ft_move_tokens(t_data *data, int *i, int *j);
void	join_tokens(t_data *d, int i, int j);

//utils.c
void	ft_free(t_tokens **arr);
void	ft_free_data(t_data *data);
int		ft_msn(char *s, int fd);
int		ft_isdelimiter(char c);
void	print_tokens(t_data *data);

#endif
