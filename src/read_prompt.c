/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:44:22 by mirifern          #+#    #+#             */
/*   Updated: 2024/07/08 00:23:24 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_initialize(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		exit(EXIT_FAILURE);
	(*data)->prompt = NULL;
	(*data)->tokens = NULL;
	return (0);
}

/*	Esto seria igual que el PWD del env
	char	current_dir[PATH_MAX + 3];

	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		ft_msn(NO_GETCWD, 2);*/
void	ft_read_prompt(t_data **data)
{
	while (1)
	{
		(*data)->prompt = readline("\033[1;34m👯 minishell> \033[0m");
		if ((*data)->prompt == NULL) //Gestiona el EOF ctr+D
		{
			ft_msn(EXIT, 2);
			break ;
		}
		if ((*data)->prompt[0] != '\0')
			add_history((*data)->prompt);
		(*data)->tokens = malloc(sizeof(t_tokens));
		if (!(*data)->tokens)
			exit(EXIT_FAILURE);
		(*data)->tokens->arr = ft_tokenize((*data)->prompt);
		//limpiar el array de tokens y rehacer la tokenizacion para que este correcta
		print_tokens((*data)->tokens->arr); //Linea a eliminar
		ft_free_data(data);
	}
	if ((*data)->prompt)
		free((*data)->prompt);
	free(*data);
}
