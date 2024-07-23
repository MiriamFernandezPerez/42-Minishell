/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/07/23 21:49:32 by esellier         ###   ########.fr       */
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

int	cd_errors(char **str)
{
	if (!str[1])
		return (0);
	if (str[2])
		return (write(2, "👯 minishell> : cd: too many arguments", 40), 1);
	if (str[1][0] == '.' || str[1][0] == '~')
	{
		if (str[1][1])
		{
			if (str[1][1] != '.' || str[1][0] == '~'
				|| str[1][1] == '.' && str[1][2])
			{
				printf("👯 minishell> : cd: %s: No such file or directory",
					str[1]);
				return (1);
			}
		}
	}
	else if (str[1][0] != '.' && str[1][0] != '~' && str[1][0] != '/')
	{
		printf("👯 minishell> : cd: %s: No such file or directory", str[1]);
		return (1);
	}
	return (0);
}
//pas de besoin d'imprimer le prompt? je crois que si, a verifier
void	change_pwd(t_data *data, char *str)
{
	t_env	*current;
	t_env	*previous;

	current = search_str("PWD", data);
	previous = search_str("OLDPWD", data);
	previous->value = current->value;
	current->value = str;
	return (data->rt_value = 0, 0);
}

int	make_cd(char **str, t_data *data)
{
	char	*tmp;
	
	if (cd_errors(str) == 1)
		return (data->rt_value == 1, 1);
	if (!str[1] || str[1][0] == '~')
	{
		if (chdir(getenv("HOME") == NULL))
		{
			change_pwd(data, getcwd(tmp, 256)); // a checker si fonctionne
			return (data->rt_value = 0, 0);
		}
		printf("cannot find 'home' directory\n");
		return (data->rt_value = 1, 1);
	}
	if (str[1][0] != '.') //absolut et relativ
	{
		if (chdir(str[1]) != 0)
		{
			printf("👯 minishell> : cd: %s: No such file or directory", str[1]);
			return (data->rt_value = 1, 1);
		}
		change_pwd(data, str[1]); // a verifier si la struct est mise a jour
		return (data->rt_value = 0, 0);
	}
	//cd .. / .
	//pour le cd.. , je choppe l'adresse actuelle avec getcwd et j.enleve le dernier
	//directory et la barre et apres chdir et change_PWD
}
// cd. = rester dans le rep courant (avec GETcwd)
// cd ~ = cd, aller au home

// faire une fonction aevc les printf/write en cas d'erreurs et leur retour pour gagner de la place?