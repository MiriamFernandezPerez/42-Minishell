/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 19:22:00 by esellier          #+#    #+#             */
/*   Updated: 2024/09/10 19:44:47 by esellier         ###   ########.fr       */
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

void	execution(t_data *data)
{
	if (data->sections_qt = 1 && make_builtins(char **str, data) == 0)
		//do builtins
	else
	{
		//creer la structure
		split_env(data->)
		if (data->sections_qt = 1)
			//do small one, builtins or simple one
		//le grand avec loops
	}

	final_free(data); // a mettre dans le main
	return ;
}