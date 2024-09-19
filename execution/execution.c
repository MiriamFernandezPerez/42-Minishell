/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:22:00 by esellier          #+#    #+#             */
/*   Updated: 2024/09/19 20:57:30 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtins_exe(t_data *data, t_section *section)
{
	if (section->fd_in != -2)
	{
		if (dup2(section->fd_in, STDIN_FILENO) == -1)
			return (error_exe(data, NULL, 2)); // trouver le moyen de sortir completement
		close (section->fd_in);
	}
	if (section->fd_out != -2)
	{
		if (dup2(section->fd_out, STDOUT_FILENO) == -1)
			return (error_exe(data, NULL, 2));// trouver le moyen de sortir completement
		close (section->fd_out);
	}
	data->rt_value = make_builtins(section->cmd, data);
	ft_free_section(data->sections);
	return (data->rt_value);
}

void	classic_exe(t_data *data, t_section *section)
{
	section->path_array = lst_to_arr(data->env_lst, data, section->path_array);
	if (search_path(data, section->path_array, section) != 0)
		return (data->rt_value);
	if (section->fd_in != -2)
	{
		if (dup2(section->fd_in, STDIN_FILENO) == -1)
			return (error_exe(data, NULL, 2)); // trouver le moyen de sortir completement
		close (section->fd_in);
	}
	if (section->fd_out != -2)
	{
		if (dup2(section->fd_out, STDOUT_FILENO) == -1)
			return (error_exe(data, NULL, 2));// trouver le moyen de sortir completement
		close (section->fd_out);
		if (section->next->fd_in != -2) // si c'est un pipe ca ferme la sortie de lecture pour pas aue ca sorte si autre chose ca fait rien car dans l'enfant
			close (section->next->fd_in);
	}
	if (execve(section->path, section->cmd, section->path_array) == -1)
		exit (error_exe(data, "execve", 0));
}

void	close_fd(t_section *section)
{
	if (section->fd_out != -2) // et -1
		close (section->fd_out);
	if (section->fd_in != -2)
		close (section->fd_in);
	return ;
}

/*int	*ft_waitpid(t_section *section)
{
	int	status;

	waitpid(section->pid, &status, 0);
	return (status);
}

int	ft_waitpid_status(t_section *section)
{
	int	*status;
	int	i;

	while (section)
	{
		status = ft_waitpid(section);
		section = section->next;
		i++;
	}
	if (WIFEXITED(status[i]))
		return (WEXITSTATUS(status[i]));
	if (WIFSIGNALED(status[i]))
		return (WTERMSIGN(status[i]));
}*/

int	ft_waitpid_status(t_section *section)
{
	int	**status;
	int	i;

	status = (int **)malloc(sizeof (int *));
	while (section)
	{
		waitpid(section->pid, status[i], 0);
		section = section->next;
		i++;
	}
	if (WIFEXITED(status[i]))
		return (WEXITSTATUS(status[i]));
	if (WIFSIGNALED(status[i]))
		return (WTERMSIGN(status[i]));
}

void	execution(t_data *data, t_section *section)
{
	if (data->sections_qt == 1 && check_builtins(section->cmd) == 0)
	{
		if (section->fd_in != -1 && section->fd_out != -1)
			return (builtins_exe(data, section));
		else
			return (ft_free_section(data->sections), data->rt_value);
	}
	while (section)
	{
		if (section->fd_in != -1 && section->fd_out != -1)
		{
			section->pid = fork();
			if (section->pid < 0)
				return (perror("Fork error"), ft_free_data(data), exit(1));
			if (section->pid == 0)
			{
				if (check_builtins(section->cmd) == 1)
					return (classic_exe(data, section));
				if (make_builtins(section->cmd, data) == 1)
					exit(1);
				else
					exit(0);
				// a voir si ok de pas free la data a la fin du hijo
			}
		}
		if (!section->next && (section->fd_in == -1 || section->fd_out == -1))
			return (ft_free_section(data->sections), data->rt_value);
		close_fd(section);
		section = section->next;
	}
	data->rt_value = ft_waitpid_status(data->sections);
	return (ft_free_section(data->sections), data->rt_value);
}
