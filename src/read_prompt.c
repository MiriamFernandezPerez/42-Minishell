/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:44:22 by mirifern          #+#    #+#             */
/*   Updated: 2024/08/13 21:34:24 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que busca si hay > >> < o << al final del prompt*/
int	find_others(char *input)
{
	int	len;

	len = ft_strlen(input) - 1;
	if (input[len] == '<' || input[len] == '>')
	{
		ft_msn(ERR_DELIM, 2);
		return (1);
	}
	return (0);
}

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

/*Funcion que llama a las funciones tokenizer, expander, del_tokens_END
join_tokens del_tokens_SPACES y verify_tokens*/
int	token_expand_clean(t_data *data)
{
	ft_tokenizer(data, ft_strlen(data->prompt), 0, 0);
	ft_expander(data);
	delete_token_type(data, END);
	join_tokens(data, 0, 0);
	delete_token_type(data, SPACES);
	if (verify_types(data) == 1)
		return (1);
	print_tokens(data);
	return (0);
}

void	free_for_new_prompt(t_data *data)
{
	free(data->prompt);
	data->prompt = NULL;
	ft_free(data->tokens);
	data->tokens = NULL;
	ft_free_sections(data->sections, data->sections_qt);
	data->sections = NULL;
}

/*1 - lee el input del prompt
2 - Si detecta un EOF (ctr+d) muestra un exit y devuelve -1 para que
se salga del bucle while(1) del main y cerrar el shell liberando
el input
3 - Anade el input al history
4 - Paso el input para depurarlo a la funcion ft_parser
5 - Tokeniza el input, lo expande y comprueba los types de cada token
...
*/
int	ft_read_prompt(t_data *data)
{
	data->prompt = readline("\033[1;34m👯 minishell> \033[0m");
	if (!data->prompt)
	{
		ft_msn(EXIT, 2);
		return (-1);
	}
	if (*data->prompt)
		add_history(data->prompt);
	if (ft_parser(data) == 1 || token_expand_clean(data) == 1)
	{
		free(data->prompt);
		data->prompt = NULL;
		ft_free(data->tokens);
		data->tokens = NULL;
		return (0);
	}
	else
		ft_sections(data);
	free_for_new_prompt(data);
	return (0);
}
