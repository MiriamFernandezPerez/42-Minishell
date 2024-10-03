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

void	ft_free_cd(t_data *data, char *old, char *new, int i)
{
	if (i == 0)
	{
		if (old)
			free (old);
		if (new)
			free (new);
		ft_malloc(data, NULL, NULL);
		return ;
	}
	if (i == 1)
	{
		perror("getcwd error: ");
		if (new)
			free (new);
		if (old)
			free (old);
		return ;
	}
}

int	change_pwd(t_data *data, char *old, char *new)
{
	t_env	*current;
	t_env	*previous;

	if (getcwd(new, 256) == 0)
		return (ft_free_cd(NULL, old, new, 1), 1);
	current = search_str("PWD", data);
	previous = search_str("OLDPWD", data);
	if (previous)
	{
		free (previous->value);
		previous->value = ft_strdup(old);
		if (!previous->value)
			ft_free_cd(data, old, new, 0);
	}
	if (current)
	{
		free (current->value);
		current->value = ft_strdup(new);
		if (!current->value)
			ft_free_cd(data, old, new, 0);
	}
	free (old);
	free (new);
	return (0);
}

int	cd_home(char **str, t_data *data)
{
	char	*old_buf;
	char	*new_buf;

	if (str[1] && str[1][1])
		return (print_errors(str, data, 1), 1);
	old_buf = ft_calloc(1, 256);
	if (!old_buf)
		ft_malloc(data, NULL, NULL);
	new_buf = ft_calloc(1, 256);
	if (! new_buf)
		ft_malloc(data, NULL, NULL);
	if (getcwd(old_buf, 256) == 0)
		return (ft_free_cd(NULL, old_buf, new_buf, 1), 1);
	if (chdir(getenv("HOME")) == 0)
		return (change_pwd(data, old_buf, new_buf));
	free (old_buf);
	free(new_buf);
	return (print_errors(str, data, 2), 1);
}

int	make_cd(char **str, t_data *data)
{
	char	*old_buf;
	char	*new_buf;

	if (str[1] && str[2])
		return (print_errors(str, data, 0), 1);
	if (!str[1] || str[1][0] == '~')
		return (cd_home(str, data));
	else
	{
		old_buf = ft_calloc(1, 256);
		new_buf = ft_calloc(1, 256);
		if (!old_buf || !new_buf)
			ft_malloc(data, NULL, NULL);
		if (getcwd(old_buf, 256) == 0)
			return (ft_free_cd(NULL, old_buf, NULL, 1), 1);
		if (chdir(str[1]) != 0)
			return (print_errors(str, data, 1), 1);
		if (change_pwd(data, old_buf, new_buf) == 1)
			ft_malloc(data, NULL, NULL);
	}
	return (0);
}

int	make_pwd(t_data *data)
{
	char	*buf;

	buf = ft_calloc(1, 256 * sizeof(char));
	if (!buf)
		ft_malloc(data, NULL, NULL);
	if (getcwd(buf, 256) == 0)
	{
		perror("getcwd error: ");
		return (free(buf), 1);
	}
	else
		printf("%s\n", buf);
	return (free(buf), 0);
}
//getcwd = fonction qui recupere l'adresse actuelle (fonctionne si unset PWD)
//chdir = changer de dossier, ouvrir celui indiquer et y aller
//getenv = choppe une ligne dans l'environnement