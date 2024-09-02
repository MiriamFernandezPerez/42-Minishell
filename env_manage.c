/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:14:34 by esellier          #+#    #+#             */
/*   Updated: 2024/09/02 19:47:17 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*env_new(char *str, t_env *new_node)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	new_node->name = malloc((i + 1) * sizeof(char));
	if (!new_node->name)
		return (free(new_node), NULL);
	ft_strlcpy(new_node->name, str, i + 1);
	new_node->name[i] = '\0';
	j = 0;
	while (str[i++])
		j++;
	new_node->value = malloc((j + 1) * sizeof(char));
	if (!new_node->value)
		return (free(new_node), NULL);
	ft_strlcpy(new_node->value, &str[i - j], j);
	new_node->value[j] = '\0';
	if (ft_strcmp(new_node->name, "_") == 0)
		new_node->flag = 'X';
	else
		new_node->flag = 'v';
	new_node->print = 0;
	return (new_node);
}

t_env	*create_env(char **env)
{
	int		i;
	t_env	*env_lst;
	t_env	*temp;
	t_env	*new_node;

	i = 0;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (0);
	env_lst = env_new(env[i], new_node);
	temp = env_lst;
	i++;
	while (env[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (0);
		env_lst->next = env_new(env[i], new_node);
		env_lst = env_lst->next;
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
int	create_value(t_env *new_node, int i, int j, char *str)
{
	if (j > 1)
	{
		new_node->value = malloc((j + 1) * sizeof(char));
		if (!new_node->value)
		{
			free(new_node->name);
			return (free(new_node), 1);
		}
		ft_strlcpy(new_node->value, &str[i - j], j + 1);
	}
	return (0);
}

int	exp_new(char *str, t_env *new_node)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	new_node->name = malloc((i + 1) * sizeof(char));
	if (!new_node->name)
		return (free(new_node), 1);
	ft_strlcpy(new_node->name, str, i + 1);
	new_node->name[i] = '\0';
	j = 0;
	while (str[i++])
		j++;
	if (create_value(new_node, i, j, str) == 1)
		return (1);
	if (j < 2)
		new_node->value = '\0';
	new_node->flag = 'v';
	if (j == 1)
		new_node->flag = 'V';
	if (j == 0)
		new_node->flag = 'W';
	new_node->print = 0;
	return (0);
}

//check si pas d'erreur de free avec la value NULL sans malloc

	/*printf("NAME= %s\n", new_node->name);
	if (new_node->value)
		printf("VALUE= %s\n", new_node->value);
	printf("FLAG= %d\n", new_node->flag);*/

void	ft_free(char **array)
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

int	env_array(t_data **data, char **array)
{
	t_env	*env;
	int		i;

	i = 0;
	array = (char **)malloc(sizeof (char));
	if (!array)
		return (1);
	env = (*data)->env_lst;
	while (env)
	{
		array[i] = malloc(ft_strlen(env->name) + ft_strlen(env->value)
				+ 2 * sizeof(char));
		if (!array[i])
			return (ft_free(array), 1);
		//ft_envjoin(env->name, env->value, array[i]);
		if (env->name)
		{
			ft_strlcpy(array[i], env->name, ft_strlen(env->name) + 1);
			ft_strlcat(array[i], "=", ft_strlen(env->name) + 1);
			if (env->value)
				ft_strlcat(array[i], env->value, ft_strlen(env->name) + 2);
		}
		i++;
	}
	array[i] = '\0';
	return (0);
}

/*char	*ft_envjoin(char *s1, char *s2, char *dst)
{
	if (s1)
	{
		ft_strlcpy(dst, s1, ft(strlen(s1)) + 1);
		ft_strlcat(dst, "=", ft(strlen(s1)) + 1);
		if (s2)
			ft_strlcat(dst, s2, ft(strlen(s1) + 2));
	}
	return (0);
}*/
