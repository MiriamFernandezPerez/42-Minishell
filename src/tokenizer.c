/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:09:23 by mirifern          #+#    #+#             */
/*   Updated: 2024/07/08 00:10:25 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Función para tokenizar la entrada
char	**ft_tokenize(char *input)
{
	int		index;
	int		len;
	int		start;
	int		end;
	char	**tokens;

	index = 0;
	if (!input)
		exit (EXIT_FAILURE);
	len = ft_strlen(input);
	start = 0;
	tokens = malloc(MAX_TOKENS * sizeof(char *));
	if (!tokens)
		exit(EXIT_FAILURE);
	while (start < len)
	{
		end = start;
		// Identificar token
		if (ft_isdelimiter(input[start]))
		{
			tokens[index] = malloc(sizeof(char) * 2);
			if (!tokens[index])
				exit(EXIT_FAILURE);
			tokens[index][0] = input[start];
			tokens[index][1] = '\0';
			index++;
			start++;
		}
		else
		{
			// Leer hasta el siguiente delimitador
			while (end < len && !ft_isdelimiter(input[end]))
				end++;
			tokens[index] = malloc(sizeof(char) * ((end - start) + 1));
			if (!tokens[index])
				exit(EXIT_FAILURE);
			ft_strlcpy(tokens[index], input + start, (end - start) + 1);
			index++;
			start = end;
		}
	}
	tokens[index] = NULL; // Terminar la lista de tokens con NULL
	return (tokens);
}

