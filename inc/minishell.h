/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:05:00 by mirifern          #+#    #+#             */
/*   Updated: 2024/09/13 17:08:17 by esellier         ###   ########.fr       */
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
# include <errno.h>

# define NO_ARGS "Error. Execution don't allow arguments\n"
# define NO_GETCWD "getcwd() error, can't read current path directory\n"
# define EXIT "exit\n"
# define ERR_SQUOTE ">\nError while looking for matching `''\n"
# define ERR_DQUOTE ">\nError while looking for matching `\"\'\n"
# define ERR_PIPE "bash: syntax error near unexpected token `|'\n"
# define ERR_SEMICOL "bash: syntax error near unexpected token `;'\n"
# define ERR_BACKSLASH "bash: syntax error near unexpected token `\\'\n"
# define ERR_DELIM "bash: syntax error near unexpected token `newline'\n"
# define ERR_INPUT "bash: syntax error near unexpected token `<'\n"
# define ERR_TRUNC "bash: syntax error near unexpected token `>'\n"
# define ERR_HEREDOC "bash: syntax error near unexpected token `<<'\n"
# define ERR_APPEND "bash: syntax error near unexpected token `>>'\n"

# define MAX_TOKENS 100
# define TOKEN_SIZE 64

//delimiters
# define CMD 0 // Command
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
# define VAR 11//Variable $

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	char			flag;
	int				print;
}				t_env;

typedef struct s_tokens
{
	char	*value;
	int		type;
}			t_tokens;

typedef struct s_section
{
	t_tokens	**tokens;
	int			tokens_qt;
}				t_section;

typedef struct s_data
{
	char		*prompt;
	t_tokens	**tokens;
	t_section	**sections;
	int			tokens_qt;
	int			sections_qt;
	int			rt_value;
	t_env		*env_lst;
}				t_data;

# include "builtins.h"
# include "execution.h"

//Main minishell.c
void		print_sections(t_data *data);
void		print_tokens(t_data *data);
int			ft_initialize(t_data **data, char **env);
int			main(int ac, char **av, char **env);

//read_prompt.c
int			find_others(char *input);
int			only_spaces(char *s);
int			token_expand_clean(t_data *data);
void		free_for_new_prompt(t_data *data);
int			ft_read_prompt(t_data *data);

//parse.c
int			end_quote(char *input, char c, int i);
int			find_pipes(char *input);
int			find_pair_quote(char *input, int *i, char quote_type);
int			find_quotes(char *input, int squote, int dquote);
int			ft_parser(t_data *data);

//tokenize.c
int			end_variable(char *input, int i);
void		tok_delimiter(t_data *data, char *input, int *ind, int *start);
void		tok_nodelimiter(t_data *data, int *ind, int *start, int *end);
void		define_delimiter(t_data *data, int *start, int *end, int *index);
void		ft_tokenizer(t_data *d, int len, int start, int index);

//tokenize_utils.c
void		remove_quotes(char *str);
void		clean_quotes(t_data *d);
void		ft_move_tokens(t_data *data, int *i, int *j);
void		join_tokens(t_data *d, int i, int j);
void		delete_token_type(t_data *d, int type);


//utils2.c
void		ft_free(t_tokens **arr);
void		ft_free_data(t_data *data);
int			ft_msn(char *s, int fd);
int			ft_isdelimiter(char c);

//expander.c
char		*find_var_name(char *value, int *i);
int			find_dollar(char *str);
char		*quit_dollar(char *value, int *i);
char		*expand_var(t_data *data, char *value);
int			ft_expander(t_data *d, int i, int j);

//expander_utils.c
char		*allocate_result_buffer(void);
void		handle_rt_value(t_data *data, char **temp, char **res);
void		handle_digit_variable(char **temp, char **res);
void		handle_normal_variable(t_data *data, char **temp, char **res);
char		*expand_env_variables(t_data *data, char *input, char *temp,
				char *res);

//verify_tokens.c
void		print_err(int check);
int			check_type(int type);
void		write_msn(t_data *data, char *value);
int			verify_previous_type(t_data *d, int i, char *value);
int			verify_next_type(t_data *d);

//sections.c
void		ft_free_sections(t_section **section, int len);
void		add_token_to_section(t_section *section, t_tokens *token);
t_section	*create_section(int tokens_qt);
t_section	**split_into_sections(t_data *data, int i);
void		ft_sections(t_data *data);

//executer.c
void		ft_execute(t_data *data);

#endif