/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/07/12 19:50:47 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	make_echo(char **str) // avec char null a la fin
{
	if (str[1])
		write(1, str[1], ft_strlen(str[1]));//verifier les STDIN/ERROR des write
	if (ft_strncmp(str[0], "echo -n", 7) != 0)
		write(1, "\n", 1);
	return;
}

/*int main() // test echo
{
	char *str[2];
	
	str[0] = "echo -n";
	//str[1] = "hola que tal?";
	str[1] = '\0';
	make_echo(str);
	return(0);
}*/

int	check_path(t_env **env_lst)
{
	t_env	*current;

	current = (*env_lst);
	while (current)
	{
		if (ft_strncmp(current->name, "PATH=", 5)== 0)
			return(0);
		current = current->next;
	}
	write(1, "👯 minishell> : env: No such file or directory", 48);
	return (1);
}

t_env	**adjust_env(t_env **env_lst, t_env *to_del)
{
	t_env	*previous;
	t_env	*current;
	
	previous = NULL;
	current = (*env_lst);
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
		*env_lst = (current)->next;
	free(current);
	return (env_lst);
}

t_env	**make_unset(char **str, t_env **env_lst)
{
	t_env	*current;
	int		i;
	
	i = 1;
	while (str[i]) //check si on n'est pas en read only? ok env sans
	{
		current = (*env_lst);
		while (current)
		{
			if (ft_strncmp(str[i], current->name, ft_strlen(current->name) - 1) == 0)
			{
				env_lst = adjust_env(env_lst, current); //supprimer le node
				current = *env_lst;
			}
			else
				current = current->next;
		}
		i++; // passer a l'argument suivant si il y a
	}
	//write (1, "\n", 1);
	return (env_lst);
}

/*int main(int argc, char **argv, char **env) //unset
{
	t_env	**envi;
	(void)argc;
	t_env	*current;
	t_env	*to_print;
	
	envi = create_env(env);
	if (check_path(envi) == 1)
			return (127);
	check_path(envi);
	envi = make_unset(argv, envi);
	to_print = (*envi);
	while (to_print)
	{
        printf("%s", to_print->name);
        printf("%s\n", to_print->value);
		to_print = to_print->next;
	}
	while(*envi)
	{
		current = (*envi);
		free(current->name);
		free(current->value);
		(*envi) = current->next;
		free (current);
	}
	free (envi);
    return(0);
}*/