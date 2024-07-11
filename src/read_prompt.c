/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:44:22 by mirifern          #+#    #+#             */
/*   Updated: 2024/07/10 19:25:09 by mirifern         ###   ########.fr       */
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
void	ft_read_prompt(t_data **data)
{
	while (1)
	{
		(*data)->prompt = readline("\033[1;34m👯 minishell> \033[0m");
		printf("prompt = %s\n", (*data)->prompt);
		if ((*data)->prompt == NULL)
		{
			ft_msn(EXIT, 2);
			break ;
		}
		else if (!(only_spaces((*data)->prompt)))
		{
			add_history((*data)->prompt);
			if (parse_and_token(data, (*data)->prompt) == 0)
			{

				printf("tokenizacion completada, pasar al executor\n");
			}
		}
		free((*data)->prompt);
	}
	if ((*data)->prompt)
		free ((*data)->prompt);
	//free(data);
}
