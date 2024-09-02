/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/09/02 18:51:13 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

	if (str[1] && str[1][1]) // si quelque chose apres ~
		return (print_errors(str, data, 1), 1);
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

int	make_cd(char **str, t_data *data)
{
	if (str[0][2]) // normalement gerer par miriam avant, a verifier (cd plus quelque chose colle derriere)
		return (printf("%s: command not found\n", str[0]), 1);
	if (str[1] && str[2])
		return (print_errors(str, data,0), 1);
	if (!str[1] || str[1][0] == '~')
	{
		if (cd_home(str, data) == 1)
			return (1);
		return (0);
	}
	else
	{
		if (chdir(str[1]) != 0)
			return (print_errors(str, data, 1), 1);
		if (change_pwd(data, str[1]) == 1)
			return (printf("cannot change PWD and OLDPWD\n"), 1);
	}
	return (0);
}

// cd . (on update OLDPWD qui devient = PWD ou vide si pas de PWD (unset))
