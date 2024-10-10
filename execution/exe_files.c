/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:17:45 by esellier          #+#    #+#             */
/*   Updated: 2024/10/10 20:08:29 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc(t_data *data, char *del)
{
	char	*line;
	int		fd[2];

	if (pipe(fd) == -1)
		error_exe(data, "pipe error", 2);
	while (1)
	{
		line = NULL;
		line = readline(">");
		if (!line) //para signales (a ver si necesitamos hijo)
			break ;
		if (ft_strncmp(line, del, ft_strlen(line)) == 0)
		{
			free (line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write (fd[1], "\n", 1);
		free (line);
	}
	close (fd[1]);
	return (fd[0]);
}

int	create_file(char *file, int i, t_data *data, int fd)
{
	if (fd > -1)
		close(fd);
	if (i == INPUT)
		fd = open(file, O_RDONLY);
	else if (i == TRUNC)
		fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (i == APPEND)
		fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else if (i == HEREDOC)
		fd = ft_heredoc(data, file);
	if (fd == -1)
		error_exe(data, file, 0);
	return (fd);
}

int	fd_null(t_data *data, t_section *section)
{
	int	fd;
	int	fd2;

	if (section->fd_in == -2 && section != data->sections)
	{
		fd = open("/dev/null", O_RDONLY);
		if (fd == -1)
			error_exe(data, "open", 2);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (error_exe(data, "dup2 error", 3));
		close (fd);
	}
	if (section->fd_out == -2 && data->sections_qt > 1 && section->next)
	{
		fd2 = open("/dev/null", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd2 == -1)
			error_exe(data, "open", 2);
		if (dup2(fd2, STDOUT_FILENO) == -1)
			return (error_exe(data, "dup2 error", 3));
		close (fd2);
	}
	return (0);
}

/*
if (i == INPUT) <
	if (access(file, F_OK) == 0 && access(file, R_OK) == 0)
			fd = open(file, O_RDONLY);
		if (fd == -1 || access(file, F_OK) != 0 || access(file, R_OK) != 0)
			return (error_exe(data, file, 0));
if (i == TRUNC) <
if(access(file, F_OK) == 0 && access(file, W_OK) != 0)
			return (fd);
		fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd == -1 || access(file, R_OK | W_OK) != 0)
			return (fd); 
*/
//a checker si ok car pas teste le strerror

void	create_pipe(t_data *data)
{
	t_section	*current;
	int			tmp[2];

	current = data->sections;
	while (current && current->next)
	{
		if (current->fd_out == -2 && current->next->fd_in == -2)
		{
			if (pipe(tmp) == -1)
				error_exe(data, "pipe error", 2);
			current->fd_out = tmp[1];
			current->next->fd_in = tmp[0];
		}
		current = current->next;
	}
	return ;
}

int	check_files(t_data *data, t_section *current, t_red *red)
{
	if (data->sections)
		current = data->sections;
	while (current)
	{
		if (current->files)
		{
			red = current->files;
			while (red)
			{
				if (red->redi == INPUT || red->redi == HEREDOC)
					current->fd_in = create_file(red->file, red->redi, data,
							current->fd_in);
				if (red->redi == TRUNC || red->redi == APPEND)
					current->fd_out = create_file(red->file, red->redi, data,
							current->fd_out);
				if (current->fd_in == -1 || current->fd_out == -1)
					break ;
				red = red->next;
			}
		}
		current = current->next;
	}
	return (0);
}
