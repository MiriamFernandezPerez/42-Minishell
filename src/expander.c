/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:00:48 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/01 11:50:17 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que busca el nombre de la variable del environment*/
char	*find_var_name(char *value, int *i, t_data *data)
{
	char	*env_var;
	int		k;
	int		len;

	k = 1;
	len = 0;
	while (value[*i + k] != 32 && value[*i + k] != '\0')
		k++;
	env_var = malloc(sizeof(char *) * k);
	if (!env_var)
		ft_malloc(data, NULL, NULL);
	while (value[*i + len + 1] != 32 && value[*i + len + 1] != '\0')
	{
		env_var[len] = value[*i + len + 1];
		len++;
	}
	env_var[len] = '\0';
	*i = *i + k - 1;
	return (env_var);
}

/*Funcion que localiza dentro de un token de typo DQUOTE si hay alguna
variable para expandir*/
int	find_dollar(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1); // aqui
	write(2, "TEST\n", 5);
	write(2, str, ft_strlen(str));
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

/*Funcion que quita el dolar de la variable y el primer
numero si existe*/
char	*quit_dollar(char *value, int *i)
{
	int		j;
	char	*new_value;

	new_value = value;
	if (ft_isdigit(value[*i + 1]))
		*i = *i + 2;
	else
		*i = *i +1;
	j = 0;
	while (value[*i] != '\0')
	{
		new_value[j++] = value[(*i)++];
	}
	new_value[j] = '\0';
	if (j == 0)
		new_value = NULL;
	return (new_value);
}

/*Funcion que quita el primer $ y pasa el nombre de la variable
al environment para expandir la variable a su valor, si existe
la variable, sino devuelve NULL*/
char	*expand_var(t_data *data, char *value)
{
	t_env	*current;
	char	*new_value;
	char	*temp;

	current = data->env_lst;
	new_value = value;
	if (!new_value)
		return (NULL);
	while (current)
	{
		if (ft_strcmp(current->name, new_value) == 0)
		{
			temp = current->value;
			if (!temp)
			{
				new_value = "";
				return (new_value);
			}
			new_value = temp;
			return (new_value);
		}
		current = current->next;
	}
	return (NULL);
}

/*Funcion que identifica el tipo de token: se expandiran los de tipo VAR
y DQUOTE si tienen el signo $ en la primera posicion.
Si el primer caracter despues del $ es el signo ?, se expandira al valor
de retorno rt_value de la estructura data.
Si el primer caracter despues del $ es un numero, se eliminara el $ y el
primer numero y se devolvera el resto de los caracteres como valor
En el resto de los casos se evaluara el valor de la variable en el
environment y se expandira al valor que devuelva o a NULL si no encuentra
el nombre de la variable
Si la variable no se puede expandir y por tanto se iguala a NULL y el token
anterior es de tipo INPUT, TRUNC, o APPEND devuelvo un error, por eso creo una
copia del value del token que siempre tengo que liberar*/
int	ft_expander(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->tokens_qt)
	{
		if (d->tokens[i]->type == VAR)
		{
			if (check_previous_heredoc(d, i) == 1)
				d->tokens[i]->type = ARG;
			else
			{
				if (expand_check_and_prev(d, NULL, NULL, &i) == 1)
					return (1);
			}
		}
		i++;
	}
	return (0);
}
