/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:29:45 by esellier          #+#    #+#             */
/*   Updated: 2024/09/13 16:16:31 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

int	create_file(char *file, int i)
{
	int	fd;

	fd = -1;
	if (i == 1)
	{
		if (access(file, F_OK) == 0 && access(file, R_OK) == 0)
			fd = open(file, O_RDONLY);
		if (fd == -1 || access(file, F_OK) != 0 || access(file, R_OK) != 0)
			return (fd);
	}
	if (i == 0)
	{
		if (access(file, F_OK) == 0 && access(file, W_OK) != 0)
			return (fd);
		fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd == -1 || access(file, R_OK | W_OK) != 0)
			return (fd);
	}
	return (fd);
}

int	create_pipe(int *fd, t_args *args)
{
	if (pipe (fd) == -1)
	{
		final_free(args);
		perror("Pipe error");
		exit(1);
	}
	return (0);
}

void	return_perror(int i)
{
	if (i == 1)
		perror ("Duplication error infile");
	if (i == 0)
		perror ("Duplication error outfile");
	exit(1);
}

void	create_in_child(t_args *args, char *file, char **env)
{
	int		fd2;

	args->pid1 = fork();
	if (args->pid1 < 0)
		return (perror("Fork error infile"));
	if (args->pid1 == 0)
	{
		fd2 = create_file(file, 1);
		if (fd2 == -1)
			return ;
		if (args->cmd == NULL || args->path == NULL)
			exit(1);
		if (dup2 (fd2, 0) == -1)
			return (return_perror(1));
		close (fd2);
		if (dup2 (args->fd[1], 1) == -1)
			return (return_perror(1));
		close (args->fd[1]);
		close (args->fd[0]);
		if (execve(args->path, args->cmd, env) == -1)
		{
			perror("First command");
			exit(1);
		}
	}
}

void	create_out_child(t_args *args, char *file, char **env)
{
	int		fd2;

	args->pid2 = fork();
	if (args->pid2 < 0)
		return (perror("Fork error outfile"));
	if (args->pid2 == 0)
	{
		fd2 = create_file(file, 0);
		if (args->cmd == NULL || args->path == NULL)
			exit(127);
		if (fd2 == -1)
			exit (1);
		if (dup2 (fd2, 1) == -1)
			return (return_perror(0));
		close (fd2);
		if (dup2 (args->fd[0], 0) == -1)
			return (return_perror(0));
		close (args->fd[0]);
		if (execve(args->path, args->cmd, env) == -1)
		{
			perror("Second command");
			exit(126);
		}
	}
}
