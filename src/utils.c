/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:25:15 by esellier          #+#    #+#             */
/*   Updated: 2024/07/25 23:58:14 by mirifern         ###   ########.fr       */
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

void	env_free(t_data *data)
{
	t_env	*current;
	t_env	*previous;

	if (data->env_lst)
	{
		previous = data->env_lst;
		current = data->env_lst;
		while (current)
		{
			free(current->name);
			if (current->value)
				free(current->value);
			current = current->next;
			free(previous);
			previous = current;
		}
	}
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

//----->faire fonction si malloc fail, avec un 
//"cannot allocate memory" et retour au prompt snas continuer l'exe, 
//free de tout ce qui q ete fait avant
//mais pas la structure ou l'env

//Write environtment
void	print_env(t_data *data)
{
	t_env	*current;

	current = data->env_lst;
	while (current)
	{
		printf("%s = %s\n", current->name, current->value);
		current = current->next;
	}
}
