/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:07:08 by mirifern          #+#    #+#             */
/*   Updated: 2024/07/08 19:48:26 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_msn(char *s, int fd)
{
	if (write(fd, s, ft_strlen(s)) == -1)
		return(EXIT_FAILURE);
	else
		return(EXIT_SUCCESS);
}

int	ft_read_prompt(t_data **data)
{
/*	Esto seria igual que el PWD del env
	char	current_dir[PATH_MAX + 3];

	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		ft_msn(NO_GETCWD, 2);*/
    (*data)->prompt = readline("👯 minishell> ");
	printf("%s\n", (*data)->prompt);
	free((*data)->prompt);
    return (0);
}

int	ft_initialize(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		return(EXIT_FAILURE);
	(*data)->prompt = NULL;
	(*data)->tokens = NULL;

	return(0);
}

int main(int ac, char **av, char **env)
{
	(void)av;
	(void)env;
	//declarar structura del proyecto de momento uso puntero
	t_data	*data;

	if (ac != 1)
		return(ft_msn(NO_ARGS, 2));

	ft_initialize(&data);
    while (1)
	{
		ft_read_prompt(&data);
	}
    return (0);
}
