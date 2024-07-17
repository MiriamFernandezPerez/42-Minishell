/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:14:34 by esellier          #+#    #+#             */
/*   Updated: 2024/07/17 18:12:11 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*env_new(char *str)
{
	t_env	*new_node;
	int		i;
	int		j;
	
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	new_node->name = malloc((i + 3) * sizeof(char));
	if (!new_node->name)
		return(0);
	ft_strlcpy(new_node->name, str, i + 2);
	new_node->name[i + 2] = '\0';
	j = 0;
	while (str[i++])
		j++;
	new_node->value = malloc((j + 1) * sizeof(char));
	if (!new_node->value)
		return(0);
	ft_strlcpy(new_node->value, &str[i - j], j);
	new_node->value[j] = '\0';
	if (ft_strcmp(new_node->name, "_=") == 0)
		new_node->flag = 'x';
	else
		new_node->flag = 'v';
	return (new_node);
}

t_env *create_env(char **env)
{   
	int     i;
	t_env   *env_lst;
	t_env	*temp;

	i = 0;
	env_lst = env_new(env[i]);
	temp = env_lst;
	i++;
	while (env[i])
	{
		env_lst->next = env_new(env[i]);
		env_lst= env_lst->next;
		i++;
	}
	env_lst->next = '\0';
	env_lst = temp;
	return (env_lst);
}

/*int main(int argc, char **argv, char **env)
{
	t_env	*envi;
	(void)argc;
	(void)argv;
	t_env	*tmp;
	
	envi = create_env(env);
	tmp = envi;
	while (envi)
	{
        printf("%s", envi->name);
        printf("%s\n", envi->value);
		envi = envi->next;
	}
	envi = tmp;
	while(envi)
	{
		tmp = envi;
		free(envi->name);
		free(envi->value);
		envi = envi->next;
		free (tmp);
	}
	return(0);
}*/

t_env	*exp_new(char *str)
{
	t_env	*new_node;
	int		i;
	int		j;
	
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		new_node->name = malloc ((i + 3) * sizeof(char));
	else
		new_node->name = malloc ((i + 2) * sizeof(char)); // ou + 1  a tester
	if (!new_node->name)
		return(0);
	ft_strlcpy(new_node->name, str, i + 2); //copie le char null
	if (str[i] == '=')
	{
		new_node->name[i + 2] = '\0';
		j = 0;
		while (str[i++])
			j++;
		new_node->value = malloc ((j + 1) * sizeof(char));
		if (!new_node->value)
			return(0);
		ft_strlcpy(new_node->value, &str[i - j], j);
			new_node->value[j] = '\0';
	}
	if (ft_strcmp(new_node->name, "_=") == 0)
		new_node->flag = 'x';
	else
		new_node->flag = 'v';
	return (new_node);
}