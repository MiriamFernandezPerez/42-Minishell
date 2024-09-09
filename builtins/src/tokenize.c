/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:09:23 by mirifern          #+#    #+#             */
/*   Updated: 2024/07/25 00:40:24 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*funcion que busca el nombre completo de la variable 
cuando empieza por $ hasta encontrar otro delimitador */
int	end_variable(char *input, int i)
{
	while (input[i] != '\0')
	{
		if (ft_isdelimiter(input[i]))
			return (i - 1);
		i++;
	}
	return (i);
}

void	tok_delimiter(t_data *data, char *input, int *ind, int *start)
{
	data->tokens[*ind] = malloc(sizeof(t_tokens));
	if (!data->tokens[*ind])
		exit(EXIT_FAILURE);
	data->tokens[*ind]->value = malloc(sizeof(char) * 2);
	if (!data->tokens[*ind]->value)
	{
		free(data->tokens[*ind]);
		exit(EXIT_FAILURE);
	}
	data->tokens[*ind]->value[0] = input[*start];
	data->tokens[*ind]->value[1] = '\0';
	data->tokens[*ind]->type = ft_isdelimiter(input[*start]);
	(*ind)++;
	(*start)++;
}

void	tok_nodelimiter(t_data *data, int *ind, int *start, int *end)
{
	char	*str;

	str = malloc((*end - *start + 1) * sizeof(char));
	if (!str)
		exit(EXIT_FAILURE);
	ft_strlcpy(str, data->prompt + *start, *end - *start + 1);
	data->tokens[*ind] = malloc(sizeof(t_tokens));
	if (!data->tokens[*ind])
	{
		free(str);
		exit(EXIT_FAILURE);
	}
	data->tokens[*ind]->value = str;
	if (ft_isdelimiter(data->prompt[*start]))
	{
		data->tokens[*ind]->type = ft_isdelimiter(data->prompt[*start]);
		if (data->tokens[*ind]->type == INPUT)
			data->tokens[*ind]->type = HEREDOC;
		else if (data->tokens[*ind]->type == TRUNC)
			data->tokens[*ind]->type = APPEND;
	}
	else
		data->tokens[*ind]->type = ARG;
	(*ind)++;
	*start = *end;
}

/*Funcion que establece que tipo de delimitador ha encontrado y separa por tipos
1- Los que van entre comillas dobles o simples, 
deberemos encontrar su correspondiente comilla de cierre.
2- Si encuentra un << que lo distinga de < 
3- Si encuentra un >> que lo distinga de > 
4- Si encuentra un espacios seguidos simplemente que los omita
5- Si encuentra $ debe guardarse como tipo VAR hasta el siguiente espacio
5- De lo contrario sera un delimitador simple de tipo | < > */
void	define_delimiter(t_data *data, int *start, int *end, int *index)
{
	if (ft_isdelimiter(data->prompt[*start]) == SQUOTE
		|| ft_isdelimiter(data->prompt[*start]) == DQUOTE)
	{
		*end = end_quote(data->prompt, data->prompt[*start], *start + 1) + 1;
		tok_nodelimiter(data, index, start, end);
	}
	else if ((ft_isdelimiter(data->prompt[*start]) == INPUT
			&& ft_isdelimiter(data->prompt[*start + 1]) == INPUT)
		|| (ft_isdelimiter(data->prompt[*start]) == TRUNC
			&& ft_isdelimiter(data->prompt[*start + 1]) == TRUNC))
	{
		*end = end_quote(data->prompt, data->prompt[*start], *start + 1) + 1;
		tok_nodelimiter(data, index, start, end);
	}
	else if (ft_isdelimiter(data->prompt[*start]) == VAR)
	{
		*end = end_variable(data->prompt, *start + 1) + 1;
		tok_nodelimiter(data, index, start, end);
	}
	else if (ft_isdelimiter(data->prompt[*start]) == SPACES
		&& ft_isdelimiter(data->prompt[(*start) + 1]) == SPACES)
		(*start)++;
	else
		tok_delimiter(data, data->prompt, index, start);
}

/*Funcion que recorre el prompt en busca de delitadores tipo o 
grupos de palabras entre comillas para separar las palabras
en tokens cada uno con su tipo correspondiente*/
void	ft_tokenizer(t_data *d, int len, int start, int index)
{
	int	end;

	d->tokens = malloc(MAX_TOKENS * sizeof(t_tokens *));
	if (!d->tokens)
		exit(EXIT_FAILURE);
	while (start < len)
	{
		end = start;
		if (ft_isdelimiter(d->prompt[start]))
			define_delimiter(d, &start, &end, &index);
		else
		{
			while (end < len && !ft_isdelimiter(d->prompt[end]))
				end++;
			tok_nodelimiter(d, &index, &start, &end);
			if (index - 1 == 0)
				d->tokens[0]->type = CMD;
		}
	}
	d->tokens[index] = NULL;
	d->tokens_qt = index;
	clean_quotes(d);
}
