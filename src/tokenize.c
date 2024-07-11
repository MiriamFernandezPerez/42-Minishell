/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:09:23 by mirifern          #+#    #+#             */
/*   Updated: 2024/07/10 18:01:58 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tok_delimiter(t_data **data, char *input, int *ind, int *start)
{
	(*data)->tokens[*ind] = malloc(sizeof(t_tokens));
	if (!(*data)->tokens[*ind])
		exit(EXIT_FAILURE);
	(*data)->tokens[*ind]->value = malloc(sizeof(char) * 2);
	if (!(*data)->tokens[*ind]->value)
		exit(EXIT_FAILURE);
	(*data)->tokens[*ind]->value[0] = input[*start];
	(*data)->tokens[*ind]->value[1] = '\0';
	(*data)->tokens[*ind]->type = ft_isdelimiter(input[*start]);
	(*ind)++;
	(*start)++;
}

char	*tok_nodelimiter(t_data **data, int *ind, int *start, int end)
{
	char	*input;
	char	*str;

	input = (*data)->prompt;
	str = malloc((end - *start + 1) * sizeof(char));
	if (!str)
		exit(EXIT_FAILURE);
	ft_strlcpy(str, input + *start, end - *start + 1);
	(*data)->tokens[*ind] = malloc(sizeof(t_tokens));
	if (!(*data)->tokens[*ind])
		exit(EXIT_FAILURE);
	(*data)->tokens[*ind]->value = str;
	(*data)->tokens[*ind]->type = ARG;
	(*ind)++;
	*start = end;
	return (str);
}

int	ft_tokenizer(t_data **data, char *s, int len, int start)
{
	int	index;
	int	end;

	index = 0;
	(*data)->tokens = malloc(MAX_TOKENS * sizeof(t_tokens *));
	if (!(*data)->tokens)
		exit(EXIT_FAILURE);
	while (start < len)
	{
		end = start;
		if (ft_isdelimiter(s[start]) == 5 || ft_isdelimiter(s[start]) == 6)
		{
			end = find_end_quote(s, s[start], start + 1);
			end++;
			tok_nodelimiter(data, &index, &start, end);
		}
		else if (ft_isdelimiter(s[start]))
			tok_delimiter(data, s, &index, &start);
		else
		{
			while (end < len && !ft_isdelimiter(s[end]))
				end++;
			tok_nodelimiter(data, &index, &start, end);
		}
	}
	(*data)->tokens[index] = NULL;
	(*data)->tokens_qt = index;
	return (0);
}

/*busca que haya comillas bien cerradas y solo un pipe fuera de comillas 
y que no este al principio o al final de input*/
int	ft_parser(char *input)
{
	if (find_quotes(input, 0, 0) == 1)
		return (1);
	if (find_pipes(input) < 0)
		return (1);
	return (0);
}

/*primero hace un parseo del input para descartar posibles errores*/
int	parse_and_token(t_data **data, char *input)
{
	int		len;

	if (!input)
		exit(EXIT_FAILURE);
	len = ft_strlen(input);
	if (ft_parser(input) == 1)
		return (1);
	if (ft_tokenizer(data, input, len, 0) == 1)
		return (1);
	print_tokens(data);
	return (0);
}
