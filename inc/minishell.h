/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:05:00 by mirifern          #+#    #+#             */
/*   Updated: 2024/07/08 18:47:46 by mirifern         ###   ########.fr       */
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
int	main(int ac, char **av, char **env);

//read_prompt.c
int		ft_initialize(t_data **data);
void	ft_read_prompt(t_data **data);

//tokenizer.c
char	**ft_tokenize(char *input);

//utils.c
void	ft_free(char **arr);
void	ft_free_data(t_data **data);
int		ft_msn(char *s, int fd);
int		ft_isdelimiter(char c);
void	print_tokens(char **arr);

#endif
