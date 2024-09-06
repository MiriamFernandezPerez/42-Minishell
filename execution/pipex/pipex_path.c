/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:11:40 by esellier          #+#    #+#             */
/*   Updated: 2024/05/31 17:19:17 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

char	*search_path(char **env, int file, int i, char **argv)
{
	int		j;

	j = 0;
	while (env[j])
	{
		if (ft_strncmp("PATH=", env[j], 5) != 0)
			j++;
		else
			return (env[j]);
	}
	if (i == 1 && ((file != -1 && (ft_strncmp(argv[2], "/", 1) != 0))
			|| (ft_strncmp(argv[2], "/", 1) == 0
				&& access(argv[2], X_OK) != 0)))
		write (2, "First command: No such file or directory\n", 41);
	if (i == 0 && ((file != -1 && (ft_strncmp(argv[3], "/", 1) != 0))
			|| (ft_strncmp(argv[3], "/", 1) == 0
				&& access(argv[3], X_OK) != 0)))
	{
		write (2, "Second command: No such file or directory\n", 42);
		open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		exit(127);
	}
	return (NULL);
}

char	*path_errors(int i, char *tmp, char *str, char *argv)
{
	free (str);
	if (i == 1 && ft_strncmp(tmp, "/", 1) != 0)
		write(2, "First command not found\n", 24);
	if (i == 0 && ft_strncmp(tmp, "/", 1) != 0)
	{
		write(2, "Second command not found\n", 25);
		open(argv, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		exit(127);
	}
	return (0);
}

char	*check_path(char **array, char *str, int i, char *argv)
{
	int		j;
	char	*path;
	char	*tmp;

	j = 0;
	tmp = str;
	if (access(str, X_OK) == 0)
	{
		path = ft_strdup(str);
		return (path);
	}
	str = ft_strjoin("/", str);
	while (array[j])
	{
		path = ft_strjoin(array[j], str);
		if (access(path, F_OK | X_OK) == 0)
		{
			free(str);
			return (path);
		}
		free (path);
		j++;
	}
	path_errors(i, tmp, str, argv);
	return (NULL);
}
