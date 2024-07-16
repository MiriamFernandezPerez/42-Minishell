/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/07/16 18:50:23 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>



t_env	**adjust_env(t_env **env_lst, t_env *to_del)
{
	t_env	*previous;
	t_env	*current;
	
	previous = NULL;
	current = (*env_lst);
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
		*env_lst = (current)->next;
	free(current);
	return (env_lst);
}

t_env	**make_unset(char **str, t_env **env_lst, t_data *data)
{
	t_env	*current;
	int		i;
	
	i = 1;
	while (str[i]) //check si on n'est pas en read only? ok env sans
	{
		current = (*env_lst);
		while (current)
		{
			if (ft_strncmp(str[i], current->name, ft_strlen(current->name) - 1) == 0)
			{
				env_lst = adjust_env(env_lst, current); //supprimer le node
				current = *env_lst;
			}
			else
				current = current->next;
		}
		i++; // passer a l'argument suivant si il y a
	}
	//write (1, "\n", 1);
	data->rt_value = 0;
	return (env_lst);
}

/*int main(int argc, char **argv, char **env) //unset
{
	t_env	**envi;
	(void)argc;
	t_env	*current;
	t_env	*to_print;
	
	envi = create_env(env);
	if (check_path(envi) == 1)
			return (127);
	check_path(envi);
	envi = make_unset(argv, envi);
	to_print = (*envi);
	while (to_print)
	{
        printf("%s", to_print->name);
        printf("%s\n", to_print->value);
		to_print = to_print->next;
	}
	while(*envi)
	{
		current = (*envi);
		free(current->name);
		free(current->value);
		(*envi) = current->next;
		free (current);
	}
	free (envi);
    return(0);
}*/

int	check_path(t_env **env_lst) // pas sur aue ce soit necessaire, car c'est possible qu'on doive voir l'env dans tous les cas
{
	t_env	*current;

	current = (*env_lst);
	while (current)
	{
		if (ft_strncmp(current->name, "PATH=", 5)== 0)
			return(0);
		current = current->next;
	}
	write(1, "👯 minishell> : env: No such file or directory", 48);
	return (1);
}

void	make_env(t_env **env_lst, t_data *data)
{
	t_env	*current;
	
	current = (*env_lst);
	while(current)
	{
		printf("%s", current->name);
        printf("%s\n", current->value);
		current = current->next;
	}
	data->rt_value = 0;
	//retour prompt
	return ;
}

/*int main(int argc, char **argv, char **env) //env
{
	(void)argc;
	(void)argv;
	t_env **env_lst;
	t_env	*tmp;

	env_lst = create_env(env);
	make_env(env_lst);
	while(*env_lst)
	{
		tmp = *env_lst;
		free((*env_lst)->name);
		free((*env_lst)->value);
		(*env_lst) = (*env_lst)->next;
		free (tmp);
	}
	free (env_lst);
    return(0);
}*/


void	print_export(t_data *data)
{
	t_env	*to_print;
	t_env	*current;
	t_env	**temp;
	t_env	*old;
	
	temp = data->env_lst;
	current = *temp;
	while (current->flag != 'v')
		current = current->next;
	to_print = current;
	*temp = current;
	while(current)
	{
		if(current->flag == 'v' && ft_strcmp(current->name, to_print->name) == -1)
			to_print = current;
		current = current->next;
	}
	printf("declare -x %s%s\n", to_print->name, to_print->value);
	old = to_print;
	while(to_print == old)
	{	
		current = *temp;
		while (current->flag != 'v')
			current = current->next;
		if (!current)
			return ;
		to_print = current;
		while (current)
		{
			if(current->value && ft_strcmp(current->name, to_print->name) == -1
				&& ft_strcmp(old->name, current->name) == -1)
				to_print = current;
			current = current->next;
		}
		printf("declare -x %s%s\n", to_print->name, to_print->value);
		old = to_print;
		current->flag = 'x';		
	}
}


void	make_export(char **str, t_data *data)
{
	int i;
	t_env **env_lst;
	
	env_lst = data->env_lst;
	i = 0;
	if (!str[1])
	{
		print_export(data);
		while ((*env_lst)->next)
		{
			printf(*(env_lst));
			*env_lst = (*env_lst)->next;
		}
	}
	
}

