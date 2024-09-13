/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:24:56 by esellier          #+#    #+#             */
/*   Updated: 2024/05/31 17:51:16 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

char	**space_args(char *arg, t_args *args)
{
	int	j;

	j = 0;
	args->cmd = (char **)malloc(2 * sizeof (char *));
	if (!args->cmd)
		return (0);
	args->cmd[0] = (char *)malloc((ft_strlen(arg) + 1) * sizeof(char));
	while (arg[j])
	{
		args->cmd[0][j] = arg[j];
		j++;
	}
	args->cmd[0][j] = '\0';
	args->cmd[1] = NULL;
	return (args->cmd);
}

void	check_bar(int i, char **argv, t_args *args, char *arg)
{
	if (access(arg, X_OK) == 0)
	{
		args->path = ft_strdup(arg);
		args->cmd = ft_split(arg, ' ');
	}
	if (access(arg, X_OK) != 0)
	{
		args->cmd = NULL;
		if (i == 1)
			write (2, "First command: No such file or directory\n", 41);
		if (i == 0)
		{
			write (2, "Second command: No such file or directory\n", 42);
			open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
			exit (127);
		}
	}
}

char	**check_args(char *arg, int i, t_args *args, char **argv)
{
	int	j;

	if (!arg[0])
		return (NULL);
	if (ft_strncmp(arg, "/", 1) == 0)
	{
		check_bar(i, argv, args, arg);
		return (args->cmd);
	}
	j = 0;
	while (arg[j] == 32 || arg[j] == 9)
		j++;
	if (arg[j] == '\0')
		return (space_args(arg, args));
	if (ft_strncmp("", arg, 1) != 0)
		args->cmd = ft_split(arg, ' ');
	if (i == 0 && args->cmd == NULL && ((access(argv[4], W_OK) == 0)
			|| access(argv[4], F_OK) != 0))
		cmd_errors(argv);
	return (args->cmd);
}

void	cmd_errors(char **argv)
{
	write(2, "Second command: Permission denied\n", 34);
	open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	exit(126);
}
