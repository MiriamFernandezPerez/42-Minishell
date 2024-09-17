/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:03:19 by esellier          #+#    #+#             */
/*   Updated: 2024/09/17 17:39:28 by esellier         ###   ########.fr       */
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

char	**lst_to_array(t_env *lst, t_data *data, char **array)
{
	int		i;

	i = 0;
	array = (char **)malloc((count_lst(lst) + 1) * sizeof (char *));
	if (!array)
		ft_malloc(data, NULL, NULL);
	while(lst) //+ check si les flags qui vont dans l'env sont necessaires
	{
		if (lst->name && lst->value)
		{
			array[i] = ft_strjoin_three(lst->name, "=", lst->value);
			if (!array[i])
				ft_malloc(data, array, NULL);
		}
		if (!lst->value)
		{
			array[i] = ft_strjoin(lst->name, "=");
			if (!array[i])
				ft_malloc(data, array, NULL);
		}
		lst = lst->next;
		i++;
	}
	array[i] = '\0';
	return (array);
}

int	error_exe(t_data *data, char *arg, int i)
{
	if (i == 0)
	{
		write(2, "👯 minishell> : ", 18);
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		//et le return value?
	}
	else if (i == 1)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": command not found\n", 20);
		return (data->rt_value = 127, 127);
	}
	/*else if (i == )
	{
		write(2, "👯 minishell> : ", 18);
		write(2, arg, ft_strlen(arg));
		write(2, ": No such file or directory\n", 28);
	}
	else if (i == )
	{
		write(2, "👯 minishell> : ", 18);
		write(2, arg, ft_strlen(arg));
		write(2, ": Permission denied\n", 20);
	}
	*/
	return (data->rt_value = 1, 1);
}
//a tester le strerror
