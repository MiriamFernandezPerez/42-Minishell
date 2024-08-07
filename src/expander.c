/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:00:48 by mirifern          #+#    #+#             */
/*   Updated: 2024/08/07 20:08:41 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion que busca el nombre de la variable del environment*/
char	*find_var_name(char *value, int *i)
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
		exit(EXIT_FAILURE);
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
				free(new_value);
				return (NULL);
			}
			new_value = temp;
			return (new_value);
		}
		current = current->next;
	}
	//free (new_value);
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
el nombre de la variable*/
void	ft_expander(t_data *d)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < d->tokens_qt)
	{
		if (d->tokens[i]->type == VAR)
		{
			res = expand_env_variables(d, d->tokens[i]->value, NULL, NULL);
			d->tokens[i]->value = res;
			if (res[0] == '\0')
				d->tokens[i]->type = END;
			else
				d->tokens[i]->type = ARG;
			j++;
		}
		i++;
	}
}
