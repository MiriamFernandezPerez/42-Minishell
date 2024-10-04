/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_prompt_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:11:35 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/04 20:02:29 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que elimina los espacios del prompt por delante y por detras*/
void	trim_prompt(t_data *data)
{
	char	*trim_input;

	trim_input = ft_strtrim(data->prompt, " ");  
	if (!trim_input)
		ft_malloc(data, NULL, NULL);
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
