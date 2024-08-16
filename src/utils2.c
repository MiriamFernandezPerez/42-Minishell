/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:05:55 by mirifern          #+#    #+#             */
/*   Updated: 2024/08/07 21:25:17 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Function to free arrays
void	ft_free(t_tokens **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]->value);
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_free_data(t_data *data)
{
	if (data)
	{
		if (data->prompt)
		{
			free(data->prompt);
			data->prompt = NULL;
		}
		if (data->tokens)
		{
			ft_free(data->tokens);
			data->tokens = NULL;
		}
		final_free(data);
	}
}

//Write msn function
int	ft_msn(char *s, int fd)
{
	if (write(fd, s, ft_strlen(s)) == -1)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

//Check if character is a delimiter or a space
int	ft_isdelimiter(char c)
{
	if (ft_isspace(c))
		return (SPACES);
	else if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (INPUT);
	else if (c == '>')
		return (TRUNC);
	else if (c == '"')
		return (DQUOTE);
	else if (c == '\'')
		return (SQUOTE);
	else if (c == '\0')
		return (END);
	else if (c == '$')
		return (VAR);
	return (0);
}
