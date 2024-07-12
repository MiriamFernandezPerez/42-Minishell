/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:05:00 by mirifern          #+#    #+#             */
/*   Updated: 2024/07/12 21:37:56 by esellier         ###   ########.fr       */
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
}				t_env;

typedef struct s_parser
{
	char	**arr;

}			t_parser;

typedef struct s_data
{
	char		*prompt;
	t_parser	*parser;
}			t_data;

//Main minishell.c
//int	main(int ac, char **av, char **env);

//read_prompt.c
int	ft_initialize(t_data **data);
int	ft_read_prompt(t_data **data);

//tokenizer.c
char	**ft_tokenize(char *input);

//utils.c
void	ft_free(char **arr);
void	ft_free_data(t_data **data);
int		ft_msn(char *s, int fd);
int		ft_isdelimiter(char c);
void	print_tokens(char **arr);

//builtins
void	make_builtins(char **str, char **env);
void	exit_number(char **str);
void	make_exit(char **str);
void	make_env(t_env **env_lst);

//builtins_unset
void	make_echo(char **str);
int		check_path(t_env **env_lst);
t_env	**adjust_env(t_env **env_lst, t_env *to_del);
t_env	**make_unset(char **str, t_env **env_lst);

//maths
int modulo_negativ(int a);
int check_minmax(char *str);
int	strncmp_long(const char *s1, const char *s2);

//env
t_env	*ft_env_new(char *str);
t_env **create_env(char **env);


#endif
