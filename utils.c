/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:25:15 by esellier          #+#    #+#             */
/*   Updated: 2024/07/24 14:55:06 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] < s2[i])
		return (-1);
	if (s1[i] > s2[i])
		return (1);
	return (0);
}

void	final_free(t_data *data)
{
	t_env	*current;
	t_env	*previous;

	//parser
	//prompt
	if (data->env_lst)
	{
		previous = data->env_lst;
		current = data->env_lst;
		while (current)
		{
			if (current->name)
				free(current->name);
			if (current->value)
				free(current->value);
			current = current->next;
			free(previous);
			previous = current;
		}
	}
	free(data);
}

t_env	*search_str(char *str, t_data *data)
{
	t_env	*current;

	current = data->env_lst;
	while (current)
	{
		if (ft_strcmp(str, current->name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
int	print_errors(char **str, t_data *data, int i)
{
	if (i == 0)
		printf("👯 minishell> : %s: too many arguments\n", str[0]);
	if (i == 1)
		printf("👯 minishell> : %s: %s: No such file or directory\n",
			str[0], str[1]);
	if (i == 2)
		printf("cannot find 'home' directory\n");
	if (i == 3)
		printf("cannot find parent directory\n");
	if (i == 4)
		printf("cannot find current directory\n");
	return (data->rt_value = 1, 1);
	return (1);
}
//----->faire fonction si malloc fail, avec un 
//"cannot allocate memory" et retour au prompt snas continuer l'exe, free de tout ce qui q ete fait avant
//mais pas la structure ou l'env