/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:44:22 by mirifern          #+#    #+#             */
/*   Updated: 2024/07/17 21:36:57 by mirifern         ###   ########.fr       */
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

/*lee el input del prompt
lo anade al history
lo tokeniza
...
si detecta un EOF (ctr+d) muestra un exit y sale del bucle para 
cerrar el shell liberando el input a la salida del bucle
libera el prompt en cada nuevo input*/
int	ft_read_prompt(t_data *data)
{
	data->prompt = readline("\033[1;34m👯 minishell> \033[0m");
	if (!data->prompt)
	{
		write(1, "exit\n", 5);
		return (1);
	}
	if (*data->prompt)
		add_history(data->prompt);
	if (ft_parser(data->prompt) == 1)
	{
		free(data->prompt);
		return (0);
	}
	ft_tokenizer(data, ft_strlen(data->prompt), 0, 0);
	print_tokens(data);
	free(data->prompt);
	data->prompt = NULL;
	ft_free(data->tokens);
	data->tokens = NULL;
	return (0);
}
