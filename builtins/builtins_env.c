/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/07/18 17:09:42 by esellier         ###   ########.fr       */
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

t_env	*make_unset(char **str, t_data *data)
{
	t_env	*current;
	int		i;
	
	i = 1;
	while (str[i]) //check si on n'est pas en read only? ok env sans
	{
		current = data->env_lst;
		while (current)
		{
			if (ft_strncmp(str[i], current->name, ft_strlen(current->name) - 1) == 0)
			{
				data->env_lst = adjust_env(data, current); //supprimer le node
				current = data->env_lst;
			}
			else
				current = current->next;
		}
		i++; // passer a l'argument suivant si il y a
	}
	//write (1, "\n", 1);
	data->rt_value = 0;
	return (data->env_lst);
}

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

int	check_path(t_data *data) // pas sur que ce soit necessaire, car c'est possible qu'on doive voir l'env dans tous les cas
{
	t_env	*current;

	current = data->env_lst;
	while (current)
	{
		if (ft_strncmp(current->name, "PATH=", 5)== 0)
			return(0);
		current = current->next;
	}
	write(1, "👯 minishell> : env: No such file or directory", 48);
	return (1);
}

void	make_env(t_data *data)
{
	t_env	*current;
	
	current = data->env_lst;
	while(current && current->value)
	{
		printf("%s=%s\n", current->name, current->value);
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


void	print_export(t_env *env_lst)
{
	t_env	*to_print;
	t_env	*current;
	t_env	*old;
		
	current = env_lst;
	to_print = current;
	while(current)
	{
		if(current->flag == 'v' && ft_strcmp(current->name, to_print->name) == -1)
			to_print = current;
		current = current->next;
	}
	printf("declare -x %s=\"%s\"\n", to_print->name, to_print->value);
	old = to_print;
	to_print->flag = 'x';
	while(to_print == old)
	{	
		current = env_lst;
		while (current && current->flag == 'x')
			current = current->next;
		if (!current)
			return ;
		to_print = current;
		while (current)
		{
			if(current->flag == 'v' && ft_strcmp(current->name, to_print->name) == -1
				&& ft_strcmp(old->name, current->name) == -1)
				to_print = current;
			current = current->next;
		}
		printf("declare -x %s=\"%s\"\n", to_print->name, to_print->value);
		old = to_print;
		to_print->flag = 'x';
	}
	return ;
}


void	make_export(char **str, t_data *data)
{
	t_env	*current;
	int	i;
	
	current = data->env_lst;
	if (!str[1]) // pour afficher la liste des export (quand il y a seulement cette commande)
	{
		print_export(current);
		while (current) //remettre bien les flags (plus simple que copier la liste)
		{
			if (ft_strcmp(current->name, "_") != 0 && current->value)
				current->flag = 'v';
			current = current->next;
		}
		/*current = data->env_lst;
		while (current)
		{
			printf("%s%s FLAG=%d\n", current->name, current->value, current->flag);
			current = current->next;
		}*/
	}
	else
	{
		while(current->next)
			current = current->next;
		i = 1;
		while(str[i])
		{
			current->next = exp_new(str[i]);
			current = current->next;
			i++;		
		}
		current->next = NULL;
	}
	data->rt_value = 0;
	current = data->env_lst;
	while (current)
	{
		printf("%s FLAG=%d\n", current->name, current->flag);
		if (current->value)
			printf(" %s\n", current->value);
		current = current->next;
	}
	return ;
	//faire les modifs quand il y a des args
}

int main(int argc, char **argv, char **env)
{
	char *str[3];
	t_data	*data;
	(void)argc;
	(void)argv;
	//t_env	*current;
	
	data = NULL;
	str[0]= argv[1];
	str[1]= argv[2];
	//printf("%s\n", str[0]);
	//printf("%s\n", str[1]);
	str[2]= '\0';
	ft_initialize(&data, env);
	//make_env(data);
	make_export(str, data);
	/*current = data->env_lst;
	while (current)
	{
		printf("%s=%s FLAG=%d\n", current->name, current->value, current->flag);
		current = current->next;
	}*/
	final_free(data);
	return(0);
}

