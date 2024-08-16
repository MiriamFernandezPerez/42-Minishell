/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 23:27:18 by mirifern          #+#    #+#             */
/*   Updated: 2024/08/16 18:49:39 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(t_data *data)
{
    /*while (input[i] != '\0')
	{
		if (input[i] == '\\' || input[i] == ';')
		{
			if (input[i] == ';')
				ft_msn(ERR_SEMICOL, 2);
			else
				ft_msn(ERR_BACKSLASH, 2);
			return (1);
		}
		i++;
	}*/
	printf("****\n");
	print_tokens(data);
	make_exit(data->tokens, data);
	//make_echo(data->tokens);
}
