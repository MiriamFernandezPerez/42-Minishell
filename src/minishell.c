/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:07:08 by mirifern          #+#    #+#             */
/*   Updated: 2024/09/13 13:40:20 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Función de prueba para imprimir las secciones
void	print_sections(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->sections_qt)
	{
		j = 0;
		printf("SECCION %d:\n", i + 1);
		while (j < data->sections[i]->tokens_qt)
		{
			printf("  Token %d: %s (Type: %d)\n", j,
				data->sections[i]->tokens[j]->value,
				data->sections[i]->tokens[j]->type);
			j++;
		}
		i++;
	}
}

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
	if (!*env)
	{
		write(2, "⚠️⚠️⚠️\nDear evaluator,\nplease use our ", 50);
		write(2, "program with a full set environnement 😉\n", 43);
		exit (EXIT_FAILURE);
	}
	*data = malloc(sizeof(t_data));
	if (!*data)
		exit(EXIT_FAILURE);
	(*data)->prompt = NULL;
	(*data)->tokens = NULL;
	(*data)->sections = NULL;
	(*data)->tokens_qt = 0;
	(*data)->sections_qt = 0;
	(*data)->rt_value = 0;
	(*data)->env_lst = create_env(env, (*data));
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	char	**array;
	int		i;

	(void)av;
	data = NULL;
	if (ac != 1)
		return (ft_msn(NO_ARGS, 2));
	ft_initialize(&data, env);
	while (1)
	{
		i = 0;
		if (ft_read_prompt(data) == -1)
			break ;
		array = lst_to_array(data->env_lst, data);
		while (array[i])
		{
			printf("%s\n", array[i]);
			i++;
		}
	}
	if (data)
		ft_free_data(data);
	return (0);
}

/*int	main(int ac, char **av, char **env)
{
	t_data	*data;
	char	**array;
	int i = 0;

	(void)ac;
	(void)av;
	data = NULL;
	ft_initialize(&data, env);
	array = lst_to_array(data->env_lst, data);
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
	free_array(array);
	if (data)
		ft_free_data(data);
	return (0);
}*/
