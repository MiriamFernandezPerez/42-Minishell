/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_prompt_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:11:35 by mirifern          #+#    #+#             */
/*   Updated: 2024/09/30 21:05:01 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que elimina los espacios del prompt por delante y por detras*/
void	trim_prompt(t_data *data)
{
	char	*trim_input;

	trim_input = ft_strtrim(data->prompt, " ");
	if (!trim_input)
		exit(EXIT_FAILURE);
	free(data->prompt);
	data->prompt = trim_input;
}

int	find_not_allowed(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == ';')
		{
			ft_msn(ERR_SEMICOL, 2);
			return (1);
		}
		else if (input[i] == '\\')
		{
			ft_msn(ERR_BACKSLASH, 2);
			return (1);
		}
		i++;
	}
	return (0);
}
