/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/07/23 19:00:52 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	p_exp_loop(t_env *to_print, t_env *old, t_env *current, t_env *env_lst)
{
	while (to_print == old)
	{
		current = env_lst;
		while (current && (current->print == 1 || current->flag == 'X'))
			current = current->next;
		if (!current)
			return ;
		to_print = current;
		while (current)
		{
			if ((current->print == 0 && (current->flag == 'v'
						|| current->flag == 'V'))
				&& ft_strcmp(current->name, to_print->name) == -1
				&& ft_strcmp(old->name, current->name) == -1)
				to_print = current;
			current = current->next;
		}
		printf("declare -x %s=\"%s\"\n", to_print->name, to_print->value);
		old = to_print;
		to_print->print = 1;
	}
	return ;
}

void	print_export(t_env *env_lst)
{
	t_env	*to_print;
	t_env	*current;
	t_env	*old;

	current = env_lst;
	to_print = current;
	while (current)
	{
		if ((current->flag == 'v' || current->flag == 'V')
			&& ft_strcmp(current->name, to_print->name) == -1)
			to_print = current;
		current = current->next;
	}
	printf("declare -x %s=\"%s\"\n", to_print->name, to_print->value);
	old = to_print;
	to_print->print = 1;
	p_exp_loop(to_print, old, current, env_lst);
	current = env_lst;
	while (current)
	{
		if (current->print == 1)
			current->print = 0;
		current = current->next;
	}
	return ;
}

int	check_name(char *str, int i, t_env *current)
{
	char	*name;
	char	*value;
	int		j;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '=')
		return (0);
	name = malloc((i + 1) * sizeof(char));
	ft_strlcpy(name, str, i + 1);
	while (current && ft_strcmp(name, current->name) != 0)
		current = current->next;
	if (current && ft_strcmp(name, current->name) == 0 && current->value)
	{
		j = 0;
		while (str[i++])
			j++;
		value = malloc((j + 1) * sizeof(char));
		ft_strlcpy(value, &str[i - j], j + 1);
		free(current->value);
		current->value = value;
		return (free(name), 1);
	}
	return (free(name), 0);
}

int	make_export(char **str, t_data *data)
{
	t_env	*current;
	int		i;

	current = data->env_lst;
	if (!str[1])
		print_export(current);
	else
	{
		while (current->next)
			current = current->next;
		i = 1;
		while (str[i] && check_name(str[i], i, data->env_lst) == 0)
		{
			current->next = malloc(sizeof(t_env));
			if (!current->next)
				return (1);
			if (exp_new(str[i], current->next) == 1)
				return (1);
			current = current->next;
			current->next = NULL;
			i++;
		}
	}
	data->rt_value = 0;
	return (0);
}
//checkname= check si la variable existe ou non,
//si exite pas, cree le node, sinon modifie la value de celui-ci
//p_exp_loop = loops du print_export pour imprimer tous les nodes
//sauf le premier

int	main(int argc, char **argv, char **env)
{
	char	*str[4];
	t_data	*data;
	//t_env	*current;
	(void)argc;
	(void)argv;
	data = NULL;
	str[0]= argv[1];
	str[1]= argv[2];
	str[2]= argv[3];
	str[3]= '\0';
	ft_initialize(&data, env);
	//make_env(data);
	make_export(str, data);
	make_env(data);
	make_pwd(data);
	/*current = data->env_lst;
	while (current)
	{
		printf("%s=%s FLAG=%d\n", current->name, current->value, current->flag);
		current = current->next;
	}*/
	final_free(data);
	return (0);
}
//verifier avec un nom _test si dans l'export et l'env

//ATTENTION Miriam envoie les args separes de la cmd, changer les fonctions comme ca