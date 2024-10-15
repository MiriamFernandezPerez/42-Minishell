/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:11:40 by esellier          #+#    #+#             */
/*   Updated: 2024/10/15 21:48:31 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path_cmd(char **array, int j, t_data *data, char *tmp)
{
	char	*path;

	while (array[j])
	{
		path = ft_strjoin(array[j], tmp);
		if (!path)
		{
			free(tmp);
			ft_malloc(data, array, NULL);
		}
		if (access(path, F_OK | X_OK) == 0)
		{
			free(tmp);
			free_array(array);
			return (path);
		}
		free(path);
		j++;
	}
	free (tmp);
	free_array(array);
	return (NULL);
}

char	*check_path(t_section *section, t_data *data, char *path_lst)
{
	char	**array;
	int		j;
	char	*tmp;

	j = 0;
	array = split_env(path_lst);
	if (!array)
		ft_malloc(data, NULL, NULL);
	tmp = ft_strjoin("/", section->cmd[0]);
	if (!tmp)
		ft_malloc(data, array, NULL);
	return (find_path_cmd(array, j, data, tmp));
}

int	search_path(t_data *data, char **array, t_section *section)
{
	int	i;

	i = 0;
	if ((ft_strncmp(section->cmd[0], "/", 1) == 0)
		|| (ft_strncmp(section->cmd[0], ".", 1) == 0))
		return (section->path = section->cmd[0], 0);
	while (array[i])
	{
		if (ft_strncmp("PATH=", array[i], 5) == 0)
		{
			section->path = check_path(section, data, array[i]);
			if (! section->path)
			{
				if (ft_strchr(section->cmd[0], '/') != 0)
					return (error_exe(data, section->cmd[0], 0));
				return (error_exe(data, section->cmd[0], 1));
			}
			return (0);
		}
		else
			i++;
	}
	return (error_exe(data, section->cmd[0], 0));
}
/*
{
		if (access(section->cmd[0], X_OK) == 0)
			return (section->path = section->cmd[0], 0);
		return (error_exe(data, section->cmd[0], 0));
}
*/