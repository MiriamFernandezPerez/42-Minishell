/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:17:45 by esellier          #+#    #+#             */
/*   Updated: 2024/09/30 20:21:33 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc(t_data *data, char *del)
{
	char	*line;
	int		fd[2]; // ok norminette?

	if (pipe(fd) == -1)
	{
		perror("Pipe error");
		ft_free_data(data);
		exit(1);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		error_exe(data, NULL, 2);
		exit (1);
	}
	close (fd[0]);
	while (1)
	{
		line = readline(">");
		if (!line)
		{
			ft_msn(EXIT, 2);
			return (-1);
		}
		printf("%s\n", line);
		if (ft_strcmp(line, del) == 0)
			break ;
	}
	close (fd[1]);
	return (fd[0]);
}

/*int	ft_heredoc(t_data *data, t_section *section)
{
	char	**array;
	char	*tmp;
	int		*fd;
	int		i;

	i = 0;
	tmp = section->files[0]->file; //delimitador // check si les '' sont quites
	tmp = ft_strjoin(">", tmp);
	if (!tmp)
		ft_malloc(data, NULL, NULL);
	array = (char **)malloc(sizeof (char *));
	while (1)
	{
		data->prompt = readline(">");
		if (!data->prompt)
		{
			ft_msn(EXIT, 2);
			return (-1);
		}
		array[i]= malloc(sizeof (char*))
		if (ft_strcmp(data->prompt, tmp) == 0)
		{
			printf(">%s\n", data->prompt);
			break;
		}
		i++;
	}
	if (dup2(fd[0], STDOUT_FILENO) == -1);
		return (error_exe(data, NULL, 2));
	while()
		add_history(?);
	//mettre a la fin car c'est en un seul bloc que ca arrive a l'historique
	sans les > de debuts de lignes
}*/


int	create_file(char *file, int i, t_data *data)
{
	int		fd;

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
	while (current->next)
	{
		if (current->fd_out == -2 && current->next->fd_in == -2)
		{
			if (pipe(tmp) == -1)
			{
				perror("Pipe error");
				ft_free_data(data);
				exit(1);
			}
			current->fd_out = tmp[1];
			current->next->fd_in = tmp[0];
		}
		current = current->next;
	}
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
				{
					if (current->fd_in > -1)
						close (current->fd_in);
					current->fd_in = create_file(red->file, red->redi, data);
				}
				if (red->redi == TRUNC || red->redi == APPEND)
				{
					if (current->fd_out > -1)
						close(current->fd_out);
					current->fd_out = create_file(red->file, red->redi, data);
				}
				if (current->fd_in == -1 || current->fd_out == -1)
					break ;
				red = red->next;
			}
		}
		current = current->next;
	}
	return (0);
}
