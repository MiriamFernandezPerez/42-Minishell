/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:48:18 by mirifern          #+#    #+#             */
/*   Updated: 2024/07/19 21:51:57 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*FUncion que quita las comillas de los argumentos*/
void	remove_quotes(char *str)
{
	char	*src;
	char	*dst;

	src = str;
	dst = str;
	while (*src)
	{
		if (*src != '\'' && *src != '"')
			*dst++ = *src;
		src++;
	}
	*dst = '\0';
}

void	clean_tokens_end(t_data *data)
{
	while (data->tokens_qt > 0
		&& data->tokens[data->tokens_qt - 1]->type == END)
	{
		free(data->tokens[data->tokens_qt - 1]->value);
		free(data->tokens[data->tokens_qt - 1]);
		data->tokens_qt--;
	}
	data->tokens[data->tokens_qt] = NULL;
}

/*Funcion que elimina los tokens de typo SPACES y END
y quita las comillas (si hubiera) de los typo ARG*/
void	clean_tokens(t_data *data)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (i < data->tokens_qt)
	{
		if (data->tokens[i]->type != SPACES)
		{
			if (data->tokens[i]->type == ARG)
				remove_quotes(data->tokens[i]->value);
			data->tokens[index++] = data->tokens[i];
		}
		else
		{
			free(data->tokens[i]->value);
			free(data->tokens[i]);
		}
		i++;
	}
	data->tokens_qt = index;
	clean_tokens_end(data);
}

void	ft_move_tokens(t_data *data, int *i, int *j)
{
	while (*j < data->tokens_qt - 1)
	{
		data->tokens[*j] = data->tokens[*j + 1];
		(*j)++;
	}
	data->tokens_qt--;
	data->tokens[data->tokens_qt] = NULL;
	(*i)--;
}

void	join_tokens(t_data *d, int i, int j)
{
	char	*new_value;

	while (i < d->tokens_qt - 1)
	{
		if (d->tokens[i]->type == ARG && d->tokens[i + 1]->type == ARG)
		{
			new_value = malloc(ft_strlen(d->tokens[i]->value)
					+ ft_strlen(d->tokens[i + 1]->value) + 1);
			if (!new_value)
				exit(EXIT_FAILURE);
			ft_strlcpy(new_value, d->tokens[i]->value,
				ft_strlen(d->tokens[i]->value) + 1);
			ft_strlcat(new_value, d->tokens[i + 1]->value,
				(ft_strlen(new_value)
					+ ft_strlen(d->tokens[i + 1]->value)) + 1);
			free(d->tokens[i]->value);
			d->tokens[i]->value = new_value;
			free(d->tokens[i + 1]->value);
			free(d->tokens[i + 1]);
			j = i + 1;
			ft_move_tokens(d, &i, &j);
		}
		i++;
	}
}