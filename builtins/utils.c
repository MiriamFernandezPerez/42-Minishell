/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:25:15 by esellier          #+#    #+#             */
/*   Updated: 2024/10/01 14:17:19 by esellier         ###   ########.fr       */
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
	{
		//write(2, "👯 minishell> : ", 18);
		write(2, str[0], ft_strlen(str[0]));
		write(2, ": too many arguments\n", 21);
	}
	if (i == 1)
	{
		//write(2, "👯 minishell> : ", 18);
		write(2, str[0], ft_strlen(str[0]));
		write(2, ": ", 2);
		write(2, str[1], ft_strlen(str[1]));
		write(2, ": No such file or directory\n", 28);
	}
	if (i == 2)
		write(2, "bash: cd: HOME not set\n", 23);
	return (data->rt_value = 1, 1);
}

void	ft_malloc(t_data *data, char **array, t_env *lst)
{
	if (array)
		free_array(array);
	if (lst)
		erase_lst(lst);
	write(2, "malloc error, please check your computer's memory\n", 50);
	ft_free_data(data, 1);
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
		current = lst;
		while (current)
		{
			previous = current;
			if (current->name)
				free(current->name);
			if (current->value)
				free(current->value);
			current = current->next;
			free(previous);
		}
	}
}
//Write environtment
/*void	print_env(t_data *data)
{
	t_env	*current;

	current = data->env_lst;
	while (current)
	{
		printf("%s = %s\n", current->name, current->value);
		current = current->next;
	}
}*/

/*int	print_errors(char **str, t_data *data, int i)
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
} NECESSITAMOS DE IMPRIMIR EN FD2 Y NO PODEMOS CON PRINTF */


