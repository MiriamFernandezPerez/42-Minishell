/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:44:22 by mirifern          #+#    #+#             */
/*   Updated: 2024/07/08 18:46:37 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_initialize(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		exit(EXIT_FAILURE);
	(*data)->prompt = NULL;
	(*data)->parser = NULL;
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
		(*data)->parser = malloc(sizeof(t_parser));
		if (!(*data)->parser)
			exit(EXIT_FAILURE);
		(*data)->parser->arr = ft_tokenize((*data)->prompt);
		//limpiar el array de tokens y rehacer la tokenizacion para que este correcta
		print_tokens((*data)->parser->arr); //Linea a eliminar
		ft_free_data(data);
	}
	if ((*data)->prompt)
		free((*data)->prompt);
	free(*data);
}
