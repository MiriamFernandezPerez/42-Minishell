/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:57:37 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/01 12:39:45 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*allocate_result_buffer(t_data *data)
{
	char	*result;

	result = malloc(sizeof(char) * 10240);
	if (!result)
		ft_malloc(data, NULL, NULL);
	return (result);
}

/*Funcion que asigna el valor de retorno cuando recibe la variable $?
se devuelve como string pasando el int rt_value por la funcion ft_itoa*/
void	handle_rt_value(t_data *data, char **temp, char **res)
{
	char	*var_value;
	char	*original_var_value;

	(*temp)++;
	if (signal_num != 0)
		var_value = ft_itoa(signal_num);
	else
		var_value = ft_itoa(data->rt_value);
	original_var_value = var_value;
	while (*var_value != '\0')
		*(*res)++ = *var_value++;
	signal_num = 0;
	free(original_var_value);
}

void	handle_digit_variable(char **temp, char **res)
{
	if (**temp == '0')
	{
		*(*res)++ = 'b';
		*(*res)++ = 'a';
		*(*res)++ = 's';
		*(*res)++ = 'h';
	}
	(*temp)++;
	while (ft_isdigit(**temp))
		*(*res)++ = *(*temp)++;
}

void	handle_normal_variable(t_data *data, char **temp, char **res)
{
	char	var_name[128];
	char	*var_value;
	int		i;

	i = 0;
	ft_memset(var_name, 0, sizeof(var_name));
	while (**temp != '\0' && (ft_isalnum(**temp) || **temp == '_'))
		var_name[i++] = *(*temp)++;
	var_name[i] = '\0';
	var_value = expand_var(data, var_name);
	if (var_value != NULL)
	{
		while (*var_value != '\0')
			*(*res)++ = *var_value++;
	}
}

char	*expand_env_variables(t_data *data, char *input, char *temp, char *res)
{
	char	*result;

	result = allocate_result_buffer(data);
	temp = input;
	res = result;
	while (*temp != '\0')
	{
		if (*temp == '$')
		{
			temp++;
			if (*temp == '\0' || *temp == 32)
				*res++ = '$';
			else if (*temp == '?')
				handle_rt_value(data, &temp, &res);
			else if (ft_isdigit(*temp))
				handle_digit_variable(&temp, &res);
			else
				handle_normal_variable(data, &temp, &res);
		}
		else
			*res++ = *temp++;
	}
	free(input);
	*res = '\0';
	return (result);
}
