/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/07/24 19:35:53 by esellier         ###   ########.fr       */
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
			if (ft_strncmp(str[i], current->name,
					ft_strlen(current->name) - 1) == 0)
			{
				data->env_lst = adjust_env(data, current); //supprimer le node
				current = data->env_lst;
			}
			else
				current = current->next;
		}
		i++;
	}
	//write (1, "\n", 1);
	data->rt_value = 0;
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

void	make_env(t_data *data)
{
	t_env	*current;

	current = data->env_lst;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->name, current->value);
		else if (!current->value && current->flag == 'V')
			printf("%s=\n", current->name);
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

int	cd_errors(char **str, t_data *data)
{
	if (!str[1])
		return (0);
	if (str[2])
		return (print_errors(str, data, 0), 1);
	if (str[1][0] == '.' || str[1][0] == '~')
	{
		if (str[1][1])
		{
			if (str[1][1] != '.' || str[1][0] == '~'
				|| (str[1][1] == '.' && str[1][2]))
				return (print_errors(str, data, 1), 1);
		}
	}
	else if (str[1][0] != '.' && str[1][0] != '~' && str[1][0] != '/')
		return (print_errors(str, data, 1), 1);
	return (0);
}

int	change_pwd(t_data *data, char *str)
{
	t_env	*current;
	t_env	*previous;

	current = search_str("PWD", data);
	previous = search_str("OLDPWD", data);
	if (!current || !previous)
		return (1);
	if (previous)
	{
		free (previous->value);
		if (current)
			previous->value = ft_strdup(current->value);
		else
			previous->value = ft_strdup('\0');
		if (!previous->value) // comment proteger un malloc de NULL?
			return (1);
	}
	if (current)
	{
		free (current->value);
		current->value = ft_strdup(str);
		if (!current->value)
			return (1);
	}
	data->rt_value = 0;
	return(0);
}

int	make_cd(char **str, t_data *data)
{
	char	*tmp;
	int		i;

	if (cd_errors(str, data) == 1)
		return (1);
	if (!str[1] || str[1][0] == '~')
	{
		if (chdir(getenv("HOME")) == 0)
		{
			tmp = ft_calloc(1, 256);
			if (!tmp)
				return (data->rt_value = 1, 1);
			if (change_pwd(data, getcwd(tmp, 256)) == 1)// a checker si fonctionne
			{
				free (tmp);
				return (data->rt_value = 1, 1);
			}
			free (tmp);
			return (data->rt_value = 0, 0);
		}
		return (print_errors(str, data, 2), 1);
	}
	if (str[1][0] != '.') //absolut et relativ
	{
		if (chdir(str[1]) != 0)
			return (print_errors(str, data, 1), 1);
		if (change_pwd(data, str[1]) == 1)
			return (data->rt_value = 1, 1);
		return (data->rt_value = 0, 0);
	}
	else
	{
		tmp = ft_calloc(1, 256);
		if (!tmp)
				return (data->rt_value = 1, 1);
		if (str[1][1]) // a checker (cd ..)
		{
			i = 0;
			tmp = getcwd(tmp, 256);
			if (!tmp)
				return (free(tmp), 1);
			while (tmp[i])
				i++;
			while (tmp[i] != '/')
				tmp[i--] = '\0';
			tmp[i--] = '\0';
			if (chdir(tmp) != 0)
			{
				free (tmp);
				return (print_errors(str, data, 3), 1);
			}
			if (change_pwd(data, tmp) == 1)
				return (free(tmp), 1);
		}
		else//(cd .)
		{
			tmp = getcwd(tmp, 256);
			if (!tmp)
				return (free(tmp), 1);
			if (chdir(tmp) != 0)
			{
				free (tmp);
				return (print_errors(str, data, 4), 1);
			}
			if (change_pwd(data, tmp) == 1)
				return (free(tmp), 1);
		}
		free (tmp);
	}
	return (data->rt_value = 0, 0);
}
//voir si besoin de data->rt_value partout, si tout est int je peux changer dans make_builtins?
// cd . (on update OLDPWD qui devient = PWD)