/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:07:08 by mirifern          #+#    #+#             */
/*   Updated: 2024/07/24 23:40:15 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Write Tokens array
void	print_tokens(t_data *data)
{
	int		i;

	i = 0;
	printf("QT TOKENS = %d\n", data->tokens_qt);
	while (i < data->tokens_qt)
	{
		ft_putstr_fd("Token ", 1);
		ft_putnbr_fd(i, 1);
		write(1, " ", 1);
		ft_putstr_fd(data->tokens[i]->value, 1);
		ft_putstr_fd(" * Type:  ", 1);
		ft_putnbr_fd(data->tokens[i]->type, 1);
		write(1, "\n", 1);
		i++;
	}
}

/*Funcion que inicializa la estructura data
y hace una copia del environment*/
int	ft_initialize(t_data **data, char **env)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		exit(EXIT_FAILURE);
	(*data)->prompt = NULL;
	(*data)->tokens = NULL;
	(*data)->tokens_qt = 0;
	(*data)->rt_value = 0;
	(*data)->env_lst = create_env(env);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)av;
	data = NULL;
	if (ac != 1)
		return (ft_msn(NO_ARGS, 2));
	ft_initialize(&data, env);
	while (1)
	{
		if (ft_read_prompt(data) == -1)
			break ;
	}
	if (data)
		ft_free_data(data);
	return (0);
}
