/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:05:00 by mirifern          #+#    #+#             */
/*   Updated: 2024/07/24 23:39:48 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//Llibraries
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
# include <sys/types.h>
# include <sys/wait.h>

//Errors msn
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

typedef struct s_red // Miriam expand ->listas
{
	char			*file;
	int				redi; //HEREDOC/APPEND/INPUT/TRUNC
	struct s_red	*next;
}					t_red;

typedef struct s_section //->listas
{
	char				**cmd; //Miriam expand ->array
	t_red				*files; //Miriam expand -> listas
	char				**path_array; //Emilie exe
	char				*path; //Emilie exe
	int					flag; //Emilie exe
	int					pid; //Emilie exe
	int					fd_in; //Emilie exe
	int					fd_out; //Emilie exe
	int					tokens_qt; //lo necesito???
	struct s_section	*next; //Miriam expand
}						t_section;

typedef struct s_tokens
{
	char	*value;
	int		type;
}			t_tokens;

typedef struct s_data
{
	char		*prompt;
	t_tokens	**tokens;
	t_section	*sections;
	int			tokens_qt;
	int			sections_qt;
	int			rt_value;
	t_env		*env_lst;
}			t_data;

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

//read_prompt_utils.c
void    	trim_prompt(t_data *data);

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

//utils.c
int			ft_strcmp(char *s1, char *s2);
void		final_free(t_data *data);
t_env		*search_str(char *str, t_data *data);
int			print_errors(char **str, t_data *data, int i);
void		print_env(t_data *data);

//utils2.c
void		ft_free(t_tokens **arr);
void		ft_free_data(t_data *data);
int			ft_msn(char *s, int fd);
int			ft_isdelimiter(char c);

//env_manage.c
t_env		*env_new(char *str, t_env *new_node);
t_env		*create_env(char **env);
int			create_value(t_env *new_node, int i, int j, char *str);
int			exp_new(char *str, t_env *new_node);

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
t_section	*create_node(void);
void		add_redir(t_section *temp_section, t_data *data, int *i);
int			ft_isredir(int type);
void		init_sections(t_data *data);
void		ft_sections(t_data *data);

//sections_utils.c
void		add_first_redir(t_section *section, t_tokens **tokens, int *i);
void		add_rest_redir(t_section *section, t_tokens **tokens, int *i);
char		**create_cmd(t_section *section, char *arg);
int			size_cmd(char **cmd);
char		**add_arg(t_section *section, char *arg);

//builtins
void		make_builtins(char **str, t_data *data);
int			exit_number(char **str, t_data *data);
int			make_exit(t_tokens **str, t_data *data);
//int		make_exit(char **str, t_data *data);
void		make_echo(t_tokens **str);
//void	make_echo(char **str);
//void	make_rtvalue(char **str, t_data *data);
int			make_pwd(void);

//builtins_env
t_env		*adjust_env(t_data *data, t_env *to_del);
void		make_unset(char **str, t_data *data);
int			make_env(t_data *data, char **str);

//builtins_export
void		p_exp_loop(t_env *to_print, t_env *old, t_env *current,
				t_env *env_lst);
void		print_export(t_env *env_lst);
int			check_name(char *str, int i, t_env *current);
int			check_args(char *str);
int			make_export(char **str, t_data *data);

//builtins_cd
int			cd_errors(char **str, t_data *data);
int			change_pwd(t_data *data, char *str);
int			cd_home(char **str, t_data *data);
int			cd_point(char **str, t_data *data);
int			make_cd(char **str, t_data *data);

//maths.c
int			modulo_negativ(int a);
int			check_minmax(char *str);
int			strncmp_long(const char *s1, const char *s2);

//env
t_env		*env_new(char *str, t_env *new_node);
t_env		*create_env(char **env);
int			exp_new(char *str, t_env *new_node);
int			create_value(t_env *new_node, int i, int j, char *str);
//t_env **create_exp(char **str);

//executer.c
void		ft_execute(t_data *data);

//signals.c
/*void		sigint(void);
void		sigquit(void);
void		handle_signal(int sign);*/
/*void		set_signal(void);*/

#endif