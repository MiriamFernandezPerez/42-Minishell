/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/07/25 17:41:48 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		if (!previous->value)
			return (1);
	}
	if (current)
	{
		free (current->value);
		current->value = ft_strdup(str);
		if (!current->value)
			return (1);
	}
	return (0);
}

int	cd_home(char **str, t_data *data)
{
	char	*tmp;

	if (chdir(getenv("HOME")) == 0)
	{
		tmp = ft_calloc(1, 256);
		if (!tmp)
			return (1);
		if (change_pwd(data, getcwd(tmp, 256)) == 1) // a checker si fonctionne
			return (free (tmp), 1);
		return (free (tmp), 0);
	}
	return (print_errors(str, data, 2), 1);
}

int	cd_point(char **str, t_data *data) // cd .  / cd ..
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_calloc(1, 256);
	if (!tmp)
		return (1);
	tmp = getcwd(tmp, 256);
	if (!tmp)
		return (free(tmp), 1);
	if (str[1][1]) // a checker (cd ..)
	{
		while (tmp[i])
			i++;
		while (tmp[i] != '/')
			tmp[i--] = '\0';
		tmp[i--] = '\0'; 
	}
	if (chdir(tmp) != 0 && str[1][1])
		print_errors(str, data, 3);
	if (chdir(tmp) != 0 && !str[1][1]) // cd .
		print_errors(str, data, 4);
	if (chdir(tmp) != 0 || change_pwd(data, tmp) == 1)
		return (free(tmp), 1);
	return (free (tmp), 0);
}

int	make_cd(char **str, t_data *data)
{
	if (cd_errors(str, data) == 1)
		return (1);
	if (!str[1] || str[1][0] == '~')
	{
		if (cd_home(str, data) == 1)
			return (1);
	}
	else if (str[1][0] != '.') //absolut et relativ
	{
		if (chdir(str[1]) != 0)
			return (print_errors(str, data, 1), 1);
		if (change_pwd(data, str[1]) == 1)
			return (1);
	}
	else if (str[1][0] == '.')
	{
		if (cd_point(str, data) == 1)
			return (1);
	}
	return (0);
}

// cd . (on update OLDPWD qui devient = PWD ou vide si pas de PWD (unset))

/*int	make_cd(char **str, t_data *data)
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
				return (1);
			if (change_pwd(data, getcwd(tmp, 256)) == 1) // a checker si fonctionne
				return (free (tmp), 1);
			return (free (tmp), 0);
		}
		return (print_errors(str, data, 2), 1);
	}
	if (str[1][0] != '.') //absolut et relativ
	{
		if (chdir(str[1]) != 0)
			return (print_errors(str, data, 1), 1);
		if (change_pwd(data, str[1]) == 1)
			return (1);
	}
	if (str[1][0] == '.')
	{
		tmp = ft_calloc(1, 256);
		if (!tmp)
				return (1);
		tmp = getcwd(tmp, 256);
		if (!tmp)
			return (free(tmp), 1);
		if (str[1][1]) // a checker (cd ..)
		{
			i = 0;
			while (tmp[i])
				i++;
			while (tmp[i] != '/')
				tmp[i--] = '\0';
			tmp[i--] = '\0';
		}
		if (chdir(tmp) != 0 && str[1][1])
			print_errors(str, data, 3);
		if (chdir(tmp) != 0 && !str[1][1]) // cd .
			print_errors(str, data, 4);
		if (chdir(tmp) != 0 || change_pwd(data, tmp) == 1)
			return (free(tmp), 1);		
		free (tmp);
	}
	return (data->rt_value = 0, 0);
}*/