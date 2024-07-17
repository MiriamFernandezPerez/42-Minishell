/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:07:08 by mirifern          #+#    #+#             */
/*   Updated: 2024/07/09 18:54:36 by mirifern         ###   ########.fr       */
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
	(*data)->tokens_qt = 0;
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)av;
	(void)env;
	data = NULL;
	if (ac != 1)
		return (ft_msn(NO_ARGS, 2));
	ft_initialize(&data);
	while (1)
	{
		if (ft_read_prompt(data))
			break ;
	}
	ft_free_data(data);
	return (0);
}
