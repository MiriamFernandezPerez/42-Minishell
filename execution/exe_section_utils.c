/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_section_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:55:46 by esellier          #+#    #+#             */
/*   Updated: 2024/09/30 20:14:21 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*t_section	*ft_initialize_section(void)
{
	t_section	*section;

	section = malloc(sizeof (t_section));
	section->cmd = NULL; //Miriam
	section->files = NULL; //Miriam
	section->path_array = NULL;
	section->path = malloc(sizeof (char));
	section->flag = -2;
	section->pid = -2;
	section->fd_in = -2;
	section->fd_out = -2;
	section->next = NULL; //Miriam
	return (section);
}*/

void	ft_free_section(t_section *section, t_section *previous)
{
	t_red		*red;
	t_red		*prev;

	while (section)
	{
		red = NULL;
		previous = section;
		if (section->files)
			red = section->files;
		if (section->cmd)
			free_array(section->cmd);
		while (red)
		{
			prev = red;
			if (red->file)
				free(red->file);
			red = red->next;
			free(prev);
		}
		if (section->path_array)
			free_array(section->path_array);
		if (section->path)
			free(section->path);
		close_fd(section);
		section = section->next;
		free(previous);
	}
}

/*void	ft_malloc_s(t_data *data, char **array, t_env *lst, t_section *sec)
{
	if (array)
		free_array(array);
	if (lst)
		erase_lst(lst);
	write(2, "malloc error, please check your computer's memory\n", 50);
	ft_free_section(sec);
	ft_free_data(data);
	exit(1);
}*/

void	close_fd(t_section *section)
{
	if (section->fd_out > -1)
		close (section->fd_out);
	if (section->fd_in > -1)
		close (section->fd_in);
	return ;
}
