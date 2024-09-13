/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:22:00 by esellier          #+#    #+#             */
/*   Updated: 2024/09/13 17:57:57 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_data *data, t_section *exe)
{
	if (data->sections_qt == 1 && make_builtins(char **str, data) == 0)
	// == builtin et tout s'est bien passe
		//revenir au prompt
	else //plus de une section ou une non builtins
	{
		//faire la boucle
		{
			//creer l'enfant avec fork
			while(exe->files)//checker permission des fichiers
			{
				exe->files->fd = create_file(exe->files->file, exe->files->red, data);
				if (exe->files->fd == -1)
					return (data->rt_value, retourner au prompt + free tout sauf data);
				exe->files = exe->files->next;
			}
			exe->fd = exe->files->fd; //garder le dernier fd pour executer
			if (make_builtins(char **str, data) == 2) //n 'est pas un builtins 
			{
				//chercher le chemin d'acces du path si besoin (/bin pas besoin) + messages erreurs
				//fermer l'entree du pipe dupliquee avant l'exe et l'entree et sortie standard
				if (!data->env_lst)
					//si pas d'env retourner au prompt avec un message d'erreur
				exe->path_array = lst_to_array(data->env_lst);
				//execve cmd + path + message erreurs
			}
			//passer a la boucle suivante
		}
		//supprimer les struct d'exe (pas data!)
		//revenir au prompt
	}
	return ;
}

//check avec le main pour les builtins dans les sections et surtout ne pas utiliser l'execve pour eux