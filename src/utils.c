/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:05:55 by mirifern          #+#    #+#             */
/*   Updated: 2024/07/08 18:45:41 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Function to free arrays
void	ft_free(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_free_data(t_data **data)
{
	free((*data)->prompt);
	ft_free((*data)->parser->arr);
	free((*data)->parser);
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
	if (ft_isspace(c) || c == '|' || c == '>' || c == '<'
		|| c == '"' || c == '\'')
		return (1);
	return (0);
}

//Write Tokens array
void	print_tokens(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_putstr_fd("Token ", 1);
		ft_putnbr_fd(i, 1);
		write(1, " ", 1);
		ft_putstr_fd(arr[i], 1);
		write(1, "\n", 1);
		i++;
	}
}
