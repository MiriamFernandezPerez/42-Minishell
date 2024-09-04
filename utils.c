/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:25:15 by esellier          #+#    #+#             */
/*   Updated: 2024/09/04 16:22:35 by esellier         ###   ########.fr       */
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

int	print_errors(char **str, t_data *data, int i)
{
	if (i == 0)
		printf("👯 minishell> : %s: too many arguments\n", str[0]);
	if (i == 1)
		printf("👯 minishell> : %s: %s: No such file or directory\n",
			str[0], str[1]);
	if (i == 2)
		printf("cannot find 'home' directory\n");
	return (data->rt_value = 1, 1);
	return (1);
}

void	ft_malloc(t_data *data, char **array, t_env *lst)
{
	if (array)
		free_array(array);
	if (lst)
		erase_lst(lst);
	printf("malloc error, please check your computer's memory");
	final_free(data);
	exit(1);
}

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	erase_lst(t_env *lst)
{
	t_env	*current;
	t_env	*previous;

	if (lst)
	{
		previous = lst;
		current = lst;
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
}

void	final_free(t_data *data)
{
	//parser
	//prompt
	if (data->env_lst)
		erase_lst(data->env_lst);
	/*{
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
	}*/
	free(data);
}