/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:45:21 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/10 20:57:59 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que printa un error diferente por cada tipo de token delimitador*/
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

/*Funcion que devuelve el tipo de token que se detecta*/
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

void	write_msn(t_data *data, char *value)
{
	write(2, "bash: ", 6);
	write(2, value, ft_strlen(value));
	write(2, ": ambiguous redirect\n", 21);
	free(value);
	data->rt_value = 1;
}

int	verify_previous_type(t_data *d, int i, char *value)
{
	if (i == 0)
		return (2);
	if (d->tokens[i - 1] != NULL && d->tokens[i - 1]->type == SPACES)
	{
		if (d->tokens[i - 2] && (d->tokens[i - 2]->type == INPUT
				|| d->tokens[i - 2]->type == TRUNC
				|| d->tokens[i - 2]->type == APPEND))
		{
			write_msn(d, value);
			return (1);
		}
		else if (d->tokens[i - 2] && (d->tokens[i - 2]->type == HEREDOC))
		{
			d->tokens[i]->value = value;
			printf("value %s\n", value);
			printf("d->tokens[i]->value %s\n", d->tokens[i]->value);
			return (2);
		}
	}
	else if (d->tokens[i - 1]->type == INPUT || d->tokens[i - 1]->type == TRUNC
		|| d->tokens[i - 1]->type == APPEND)
	{
		write_msn(d, value);
		return (1);
	}
	else if (d->tokens[i - 1] && (d->tokens[i - 1]->type == HEREDOC))
	{
		d->tokens[i]->value = value;
		return (2);
	}
	return (0);
}

/*Funcion que verifica el siguiente tipo de token para evitar
tokens del mismo tipo juntos cuando bash devuelve error*/
int	verify_next_type(t_data *d)
{
	int	i;

	i = 0;
	while (d->tokens[i])
	{
		if (d->tokens[i]->type == INPUT || d->tokens[i]->type == TRUNC
			|| d->tokens[i]->type == HEREDOC || d->tokens[i]->type == APPEND)
		{
			if (d->tokens[i + 1] && check_type(d->tokens[i + 1]->type) == 1)
			{
				d->rt_value = 2;
				return (1);
			}
		}
		else if ((d->tokens[i]->type == PIPE)
			&& (d->tokens[i + 1]->type == PIPE))
		{
			ft_msn(ERR_PIPE, 2);
			d->rt_value = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
