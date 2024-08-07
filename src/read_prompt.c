/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:44:22 by mirifern          #+#    #+#             */
/*   Updated: 2024/08/07 21:13:19 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que verifica si el string esta compuesto
solo por espacios y/o tabulaciones*/
int	only_spaces(char *s)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (s[i] != '\0')
	{
		if (ft_isspace(s[i]))
			check++;
		i++;
	}
	if (i == check)
		return (1);
	return (0);
}

/*1 - lee el input del prompt
2 - Si detecta un EOF (ctr+d) muestra un exit y devuelve -1 para que
se salga del bucle while(1) del main y cerrar el shell liberando
el input
3 - Anade el input al history
4 - Paso el input para depurarlo a la funcion ft_parser
5 - Tokeniza el input
...
*/
int	ft_read_prompt(t_data *data)
{
	data->prompt = readline("\033[1;34m👯 minishell> \033[0m");
	if (!data->prompt)
	{
		ft_msn(EXIT, 2);
		return (-1);
	}
	if (*data->prompt)
		add_history(data->prompt);
	if (ft_parser(data) == 1)
	{
		free(data->prompt);
		data->prompt = NULL;
		return (0);
	}
	ft_tokenizer(data, ft_strlen(data->prompt), 0, 0);
	ft_expander(data);
	print_tokens(data);
	//join_tokens(data,  0, 0);
	//print_tokens(data);
	//clean_tokens_end(data);
	free(data->prompt);
	data->prompt = NULL;
	ft_free(data->tokens);
	data->tokens = NULL;
	return (0);
}
