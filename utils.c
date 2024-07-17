/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:25:15 by esellier          #+#    #+#             */
/*   Updated: 2024/07/17 17:50:13 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return(0);
	while (s1[i] && s2[i] && s1[i] == s2[i]) 
		i++;
	if (s1[i] < s2[i])
		return (-1);
	if (s1[i] > s2[i])
		return (1);
	return (0);
}

void    final_free(t_data *data)
{
	t_env   *current;
	t_env   *previous;
	
	//parser
	//prompt
	if (data->env_lst)
	{
		previous = data->env_lst;
		current = data->env_lst;
		while(current)
		{
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