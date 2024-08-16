/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:45:21 by mirifern          #+#    #+#             */
/*   Updated: 2024/08/16 21:03:28 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_err(int check)
{
	if (check == 2)
		ft_msn(ERR_PIPE, 2);
	else if (check == 3)
		ft_msn(ERR_INPUT, 2);
	else if (check == 4)
		ft_msn(ERR_TRUNC, 2);
	else if (check == 7)
		ft_msn(ERR_HEREDOC, 2);
	else if (check == 8)
		ft_msn(ERR_APPEND, 2);
}

int	check_type(int type)
{
	int	check;

	check = -1;
	if (type == INPUT)
		check = type;
	else if (type == TRUNC)
		check = type;
	else if (type == HEREDOC)
		check = type;
	else if (type == APPEND)
		check = type;
	else if (type == PIPE)
		check = type;
	if (check != -1)
	{
		print_err(check);
		return (1);
	}
	return (0);
}

int	verify_types(t_data *d)
{
	int	i;

	i = 0;
	while (d->tokens[i])
	{
		if (d->tokens[i]->type == INPUT || d->tokens[i]->type == TRUNC
			|| d->tokens[i]->type == HEREDOC || d->tokens[i]->type == APPEND
			|| d->tokens[i]->type == PIPE)
		{
			if (check_type(d->tokens[i + 1]->type) == 1)
			{
				d->rt_value = 2;
				return (1);
			}
		}
		i++;
	}
	return (0);
}
