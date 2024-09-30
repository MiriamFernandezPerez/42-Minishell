/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:05:55 by mirifern          #+#    #+#             */
/*   Updated: 2024/09/30 17:11:00 by esellier         ###   ########.fr       */
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
		if (data->sections)
		{
			//printf("num sections = %d\n", data->sections_qt);
			//ft_free_sections(data->sections, data->sections_qt);
			ft_free_section(data->sections, NULL);
			data->sections = NULL;
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
void	final_free(t_data *data)
{
	t_env	*current;
	t_env	*previous;

	//parser
	//prompt
	if (data->env_lst)
	{
		previous = data->env_lst;
		current = data->env_lst;
		while (current)
		{
			if (current->name)
				free(current->name);
			if (current->value)
				free(current->value);
			current = current->next;
			free(previous);
			previous = current;
		}
	}
	//ft_free_free(data);
}