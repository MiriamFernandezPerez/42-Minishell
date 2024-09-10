/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:05:00 by mirifern          #+#    #+#             */
/*   Updated: 2024/09/10 19:24:46 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H


typedef struct s_exe
{
	char	**cmd;
	char	**array;
	char	*path;
	int		fd[2];
	int		flag;
	int		pid1;
	int		pid2;
}			t_exe;

//split
int		count_path(char *str, char c);
int		strlen_path(char *str, char c);
//void	free_array(char **array); (same in builtins)
char	**put_path(char **array, char *str, char c, int path);
char	**split_env(char *str);

//exe


//path


#endif
