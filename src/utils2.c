/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:05:55 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/10 21:46:32 by esellier         ###   ########.fr       */
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

void	ft_free_data(t_data *data, int flag)
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
		if (data->sections)
		{
			ft_free_section(data->sections, NULL);
			data->sections = NULL;
		}
		if (flag == 1 || flag == 2)
		{
			erase_lst(data->env_lst);
			if (flag == 1)
				exit(1);
		}
	} //free data?
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
	else if (c == '\\' || c == ';')
	{
		if (c == '\\')
			ft_msn(ERR_BACKSLASH, 2);
		else
			ft_msn(ERR_SEMICOL, 2);
		exit(EXIT_FAILURE);
	}
	return (0);
}

/*void	final_free(t_data *data)
{
	t_env	*current;
	t_env	*previous;

	if (data->env_lst)
	{
		current = data->env_lst;
		while (current)
		{
			previous = current;
			if (current->name)
				free(current->name);
			if (current->value)
				free(current->value);
			current = current->next;
			free(previous);
		}
	}
	//ft_free_free(data);
}*/