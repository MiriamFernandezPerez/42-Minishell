/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/07/26 22:34:36 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*adjust_env(t_data *data, t_env *to_del)
{
	t_env	*previous;
	t_env	*current;

	previous = NULL;
	current = data->env_lst;
	while ((current) != to_del)
	{
		previous = (current);
		(current) = (current)->next;
	}
	free((current)->name);
	free((current)->value);
	if (previous)
		previous->next = (current)->next;
	if (!previous)
		data->env_lst = (current)->next;
	free(current);
	return (data->env_lst);
}

void	make_unset(char **str, t_data *data)
{
	t_env	*current;
	int		i;

	i = 1;
	while (str[i])
	{
		current = data->env_lst;
		while (current)
		{
			if (ft_strcmp(str[i], current->name) == 0)
			{
				data->env_lst = adjust_env(data, current); //supprimer le node
				current = data->env_lst;
			}
			else
				current = current->next;
		}
		i++;
	}
	return ;
}
//check si on n'est pas en read only? ok env sans

/*int main(int argc, char **argv, char **env) //unset
{
	t_env	*envi;
	(void)argc;
	t_env	*current;
	t_env	*to_print;
	
	envi = create_env(env);
	if (check_path(envi) == 1)
			return (127);
	check_path(envi);
	envi = make_unset(argv, envi);
	to_print = envi;
	while (to_print)
	{
        printf("%s", to_print->name);
        printf("%s\n", to_print->value);
		to_print = to_print->next;
	}
	while(envi)
	{
		current = envi;
		free(current->name);
		free(current->value);
		envi = current->next;
		free (current);
	}
	return(0);
}*/

/*int	check_path(t_data *data) // pas sur que ce soit necessaire, car c'est possible qu'on doive voir l'env dans tous les cas
{
	t_env	*current;

	current = data->env_lst;
	while (current)
	{
		if (ft_strncmp(current->name, "PATH=", 5)== 0)
			return(0);
		current = current->next;
	}
	write(2, "👯 minishell> : env: No such file or directory", 48);
	return (1);
}*/

int	make_env(t_data *data, char **str)
{
	t_env	*current;

	if (str[1])
		return (printf(" env: '%s': No such file or directory\n", str[1]), 1);
	current = data->env_lst;
	if (!current)
		return (printf("👯 minishell> : env: No such file or directory\n"), 1);
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->name, current->value);
		else if (!current->value && current->flag == 'V')
			printf("%s=\n", current->name);
		current = current->next;
	}
	return (0);
}
//voir avec Miriam comment gerer si pas d.environnement pour la suite des commandes? On sort, on fait rien?

/*int main(int argc, char **argv, char **env) //env
{
	(void)argc;
	(void)argv;
	t_env *env_lst;
	t_env	*tmp;

	env_lst = create_env(env);
	make_env(env_lst);
	while(env_lst)
	{
		tmp = env_lst;
		free(env_lst->name);
		free(env_lst->value);
		env_lst = env_lst->next;
		free (tmp);
	}
    return(0);
}*/

