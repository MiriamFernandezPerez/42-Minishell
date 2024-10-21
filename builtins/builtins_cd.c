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
	if (i == 1)
		perror("getcwd error: ");
	if (old)
	{
		free (old);
		old = NULL;
	}
	if (new)
	{
		free (new);
		new = NULL;
	}
	if (i == 0)
		ft_malloc(data, NULL, NULL);
	return ;
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
	change_cd_data(data, new);
	free (new);
	return (0);
}

int	cd_home(char **str, t_data *data, int i)
{
	char	*old_buf;
	char	*new_buf;
	char	*tmp;

	//if (str[1] && str[1][1] && !)
	//	return (print_errors(str, data, 1), 1);
	old_buf = ft_calloc(1, 256);
	if (!old_buf)
		ft_malloc(data, NULL, NULL);
	new_buf = ft_calloc(1, 256);
	if (!new_buf)
	{
		free (old_buf);
		ft_malloc(data, NULL, NULL);
	}
	tmp = getenv("HOME");
	if (i == 0 && (!tmp || search_str("HOME", data) == 0))
	{
		free (old_buf);
		free (new_buf);
		return (print_errors(str, data, 2), 1);
	}
	/*if (i == 0 && getcwd(old_buf, 256) == 0) //check data car on doit tjr l'avoir?
		return (ft_free_cd(NULL, old_buf, new_buf, 1), 1);*/
	//if (i == 1)
	old_buf = data->current_dir;
	if (chdir(tmp) == 0)
		return (change_pwd(data, old_buf, new_buf));
	free (old_buf);
	free (new_buf);
	return (print_errors(str, data, 2), 1);
}

int	make_cd(char **str, t_data *data)
{
	char	*old_buf;
	char	*new_buf;

	if (str[1] && str[2])
		return (print_errors(str, data, 0), 1);
	if (!str[1])
		return (cd_home(str, data, 0));
	if (str[1] && str[1][0] == '~')
	{
		if (str[1][1])
			return (print_errors(str, data, 1), 1);
		return (cd_home(str, data, 1));
	}
	else
	{
		old_buf = ft_calloc(1, 256);
		if (!old_buf)
			ft_malloc(data, NULL, NULL);
		new_buf = ft_calloc(1, 256);
		if (!new_buf)
		{
			free (old_buf);
			ft_malloc(data, NULL, NULL);
		}
		if (getcwd(old_buf, 256) == 0)
			//cd_home
			//return (ft_free_cd(NULL, old_buf, new_buf, 1), 1);//ici retourner au home ?
		if (chdir(str[1]) != 0)
		{
			free (old_buf);
			free(new_buf);
			return (print_errors(str, data, 1), 1);
		}
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
		//check data->current_dir; //doit fonctionner qnd fichier supprime
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

//test quand je supprime le dossier au dessus , sortir de la boucle
//celui ou je suis, attention erreur de pwd quand ca devrait etre erreur de execve
//PWD a changer, doit tjr fonctionner, mettre la data si getcwd ne fonctionne pas
// cd. devrait faire =  cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
//idem cd ..
//cd (si pas unset HOME doit foctionner directement)