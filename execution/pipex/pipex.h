/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:15:32 by esellier          #+#    #+#             */
/*   Updated: 2024/05/31 18:43:13 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_args
{
	char	**cmd;
	char	**array;
	char	*path;
	int		fd[2];
	int		flag;
	int		pid1;
	int		pid2;
}			t_args;

t_args	*structure(void);
void	return_perror(int i);
char	**split_env(char *str);
void	cmd_errors(char **argv);
int		final_free(t_args *args);
void	free_array(char **array);
int		count_path(char *str, char c);
int		create_file(char *file, int i);
int		strlen_path(char *str, char c);
int		create_pipe(int *fd, t_args *args);
char	**space_args(char *arg, t_args *args);
char	*path_errors(int i, char *tmp, char *str, char *argv);
char	**put_path(char **array, char *str, char c, int path);
void	create_in_child(t_args *args, char *file, char **env);
void	check_bar(int i, char **argv, t_args *args, char *arg);
void	create_out_child(t_args *args, char *file, char **env);
char	*check_path(char **array, char *str, int i, char *argv);
char	*search_path(char **env, int infile, int i, char **argv);
char	**check_args(char *arg, int i, t_args *args, char **argv);
int		first_check(t_args *args, int argc, char **argv, char **env);
char	*check_file(char *file, t_args *args, char **env, char **argv);

#endif