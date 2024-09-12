/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:22:00 by esellier          #+#    #+#             */
/*   Updated: 2024/09/12 19:18:20 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
t_args	*structure(void)
{
	t_args	*args;

	args = (t_args *)malloc(sizeof(t_args));
	if (!args)
	{
		write(2, "Structure error\n", 16);
		exit(1);
	}
	args->path = NULL;
	args->cmd = NULL;
	args->array = NULL;
	args->flag = 0;
	args->pid1 = 5;
	args->pid2 = 5;
	return (args);
}

void	execution(t_data *data, t_section *exe)
{
	if (data->sections_qt == 1 && make_builtins(char **str, data) == 0)
	// == builtin et tout s'est bien passe
		//revenir au prompt
	else //plus de une section ou une non builtins
	{
		//creer la structure section
		//faire la boucle
			//creer l'enfant avec fork
			//checker si c'est un builtins
			//chercher le chemin d'acces du path si besoin (/bin pas besoin) + messages erreurs
			//checker si on a les droits des fichiers et les creer et creer les fd pour chaques + messages erreurs
			//fermer l'entree du pipe dupliquee avant l'exe et l'entree et sortie standard
			//exe->path_array = //transfo la lst env en array au dernier moment!
			//execve cmd + path + message erreurs
		//suprimer les struct d'exe (pas data!)
		//revenir au prompt
	}
	return ;
}

//check avec le main pour les builtins dans les sections et surtout ne pas utiliser l'execve pour eux