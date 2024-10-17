/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:03:19 by esellier          #+#    #+#             */
/*   Updated: 2024/10/17 21:38:12 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3)
{
	size_t	ls;
	size_t	ls1;
	size_t	ls2;
	char	*m;

	ls = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s1) + ft_strlen(s2);
	if (s1 && s2 && s3)
	{
		m = (char *)malloc(ls + 1);
		if (!m)
			return (NULL);
		ft_strlcpy(m, s1, ls1 + 1);
		ft_strlcat(m, s2, ls2 + 1);
		ft_strlcat(m, s3, ls + 1);
		return (m);
	}
	return (NULL);
}

int	check_builtins(char **str)
{
	if ((ft_strcmp("echo", str[0]) == 0) || (ft_strcmp("cd", str[0]) == 0)
		|| (ft_strcmp("pwd", str[0]) == 0) || (ft_strcmp("export", str[0]) == 0)
		|| (ft_strcmp("unset", str[0]) == 0) || (ft_strcmp("env", str[0]) == 0)
		|| (ft_strcmp("exit", str[0]) == 0))
		return (0);
	else
		return (1);
}

void	exe_builtins_redi(t_data *data, int fd_in, int fd_out)
{
	if (dup2(fd_out, STDOUT_FILENO) == -1 || dup2(fd_in, STDIN_FILENO) == -1)
	{
		close (fd_in);
		close (fd_out);
		error_exe(data, "Dup2 error", 2);
		exit(1);
	}
	close (fd_in);
	close (fd_out);
	return ;
}
//function who put back STDIN and STDOUT to the origin
//(because there is no child in builtins when we do dup2)