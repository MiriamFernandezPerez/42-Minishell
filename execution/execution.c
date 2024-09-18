/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:22:00 by esellier          #+#    #+#             */
/*   Updated: 2024/09/18 20:48:46 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	execution(t_data *data, t_section *section)
{
	if (data->sections_qt == 1 && make_builtins(section->cmd, data) != 2)
		return (data->rt_value);
	else
	{
		while (section)
		{
			section->pid = fork();
			if (section->pid < 0)
				return (perror("Fork error"), ft_free_data(data), exit(1));
			if (section->pid == 0)
			{
				if (make_builtins(section->cmd, data) == 2)
					return (classic_exe(data, section));
				if (make_builtins(section->cmd, data) == 1)
					exit(1);
				else
					exit(0);
			}
			if (section->fd_out != -2)
				close (section->fd_out);
			if (section->fd_in != -2)
				close (section->fd_in);
			section = section->next;
			//waitpid
			// a voir si ok de pas free data a la fin du hijo
		}
		return (ft_free_section(data->sections), 0);
	}
}

//check avec le main pour les builtins dans les sections et surtout ne pas utiliser l'execve pour eux