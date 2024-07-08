/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:05:00 by mirifern          #+#    #+#             */
/*   Updated: 2024/07/08 19:46:24 by esellier         ###   ########.fr       */
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

typedef struct s_tokens
{
	char	**arr_token;

}			t_tokens;

typedef struct s_data
{
	char		*prompt;
	t_tokens	*tokens;
}			t_data;

//builtins
void	make_builtins(char **str);
void	make_exit(char **str);

//maths
int modulo_negativ(int a);

#endif
