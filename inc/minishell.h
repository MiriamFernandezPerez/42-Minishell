/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:05:00 by mirifern          #+#    #+#             */
/*   Updated: 2024/09/03 19:38:35 by esellier         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define NO_ARGS "Error. Execution don't allow arguments\n"
# define NO_GETCWD "getcwd() error, can't read current path directory\n"
# define EXIT "exit\n"

# define MAX_TOKENS 100
# define TOKEN_SIZE 64
# define PIPE 

/*
typedef struct s_tokens
{
	char	*value;
	char	*expander;
	char	*TYPE (Command/file/delimiters);
	t_tokens	*previous;
	t_tokens	*next;
}			t_tokens;*/

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	char			flag;
	int				print;
}				t_env;

typedef struct s_parser
{
	char	**arr;

}			t_parser;

typedef struct s_data
{
	char		*prompt;
	t_parser	*parser;
	int			rt_value;
	t_env		*env_lst;

}			t_data;

//Main minishell.c
//int	main(int ac, char **av, char **env);

//read_prompt.c
int		ft_initialize(t_data **data, char **env);
int		ft_read_prompt(t_data *data);

//tokenizer.c
char	**ft_tokenize(char *input);

//utils.c
void	ft_free(char **arr);
void	ft_free_data(t_data *data);
int		ft_msn(char *s, int fd);
int		ft_isdelimiter(char c);
void	print_tokens(char **arr);

//builtins
void	make_builtins(char **str, t_data *data);
int		exit_number(char **str, t_data *data);
int		make_exit(char **str, t_data *data);
void	make_echo(char **str);
//void	make_rtvalue(char **str, t_data *data);
int		make_pwd(t_data *data);

//builtins_env
t_env	*adjust_env(t_data *data, t_env *to_del);
void	make_unset(char **str, t_data *data);
int		make_env(t_data *data, char **str);

//builtins_export
void	p_exp_loop(t_env *to_print, t_env *old, t_env *current, t_env *env_lst);
void	print_export(t_env *env_lst);
int		check_name(char *str, int i, t_env *current, t_data *data);
int		check_args(char *str);
int		make_export(char **str, t_data *data);


//builtins_cd
int		change_pwd(t_data *data, char *str);
int		cd_home(char **str, t_data *data);
int		make_cd(char **str, t_data *data);
//maths
int		modulo_negativ(int a);
int		check_minmax(char *str);
int		strncmp_long(const char *s1, const char *s2);

//env
t_env	*env_new(char *str, t_env *new_node);
t_env	*create_env(char **env, t_data *data);
int		exp_new(char *str, t_env *new_node);
int		create_value(t_env *new_node, int i, int j, char *str);
t_env	*search_str(char *str, t_data *data);

//env_array
char	**copy_env(t_data *data, char **array, t_env *env);
char	**env_array(t_data *data, char **array);

//utils
int		ft_strcmp(char *s1, char *s2);
void	final_free(t_data *data);
int		print_errors(char **str, t_data *data, int i);
void	ft_malloc(t_data *data, char **array, t_env *lst);
void	free_array(char **arr);
void	erase_lst(t_env *lst);

#endif
