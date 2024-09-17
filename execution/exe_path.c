/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:11:40 by esellier          #+#    #+#             */
/*   Updated: 2024/09/17 18:43:10 by esellier         ###   ########.fr       */
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
	free_array(array);
	return (NULL);
}

char	*check_path(t_section *section, t_data *data, char *path_lst)
{
	char	**array;
	int		j;
	char	*tmp;
	char	*path;

	j = 0;
	array = split_env(path_lst);
	if (!array)
		ft_malloc(data, NULL, NULL);
	tmp = ft_strjoin("/", section->path);
	if (!tmp)
		ft_malloc(data, array, NULL);
	return (find_path_cmd(array, j, data, tmp));
}

int	search_path(t_data *data, char **array, t_section *section)
{
	int	i;

	i = 0;
	if ((ft_strncmp(section->cmd[0], '/', 1) == 0)
		|| (ft_strncmp(section->cmd[0], '.', 1) == 0))
		return (section->path = section->cmd[0], 0);
	while (array[i])
	{
		if (ft_strncmp("PATH=", array[i], 5) != 0)
			i++;
		else
		{
			section->path = check_path(section, data, array[i]);
			if (! section->path)
				return (error_exe(data, section->cmd[0], 1)); //checker si ok rt_value (127)
			return (0);
		}
	}
	error_exe(data, section->cmd[0], 0);//si PATH unset (No such file or directory)
	return (data->rt_value = 127); // verifier si ok
}
// checker si ok avec le malloc general a l'initialisation
