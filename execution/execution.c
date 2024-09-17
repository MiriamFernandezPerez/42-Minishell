/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:22:00 by esellier          #+#    #+#             */
/*   Updated: 2024/09/17 19:03:21 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_data *data)
{
	t_section	*section;
	t_red		*red;

	section = data->sections;
	red = section->files; // voir pour passer en args de la fonction si trop long les 4 lignes ci dessus
	if (data->sections_qt == 1 && make_builtins(section->cmd, data) == 0)
		// == builtin et tout s'est bien passe;
		revenir au prompt;
	else
	{
		while (section)
		{
			section->pid = fork();
			if (section->pid < 0)
				return (perror("Fork error")); + free tout sauf data?// a checker
			if (section->pid > 0)
				on est dans le padre? le mettre avec le fork error?
			if (make_builtins(section->cmd, data) == 2) //n 'est pas un builtins 
			{
				if (!data->env_lst)
					//si pas d'env retourner au prompt avec un message d'erreur;
				section->path_array = lst_to_array(data->env_lst, data, section->path_array);
				if (search_path(data, section->path_array, section) != 0);
					return (data->rt_value, free tout sauf data);
				//fermer l'entree du pipe + redirection des files si redirection
				//execve cmd + path + message erreurs // on sort de l'enfant, garder le pid
				//gerer la rt_value
			}
			//si builtins + on sort de l'enfant garder le pid
			// a voir si ok de pas free data a la fin du hijo
			section = section->next;
		}
		//supprimer les struct d'exe (pas data!)
		//revenir au prompt
	}
	return ;
}

//check avec le main pour les builtins dans les sections et surtout ne pas utiliser l'execve pour eux