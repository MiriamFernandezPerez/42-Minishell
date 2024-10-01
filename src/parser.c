/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:44:10 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/01 14:48:13 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*funcion que busca el mismo tipo de comilla que char c
(comilla doble o simple) y devuelve el contador que es la
posicion donde la funcion find_pipe debe seguir avanzando*/
int	end_quote(char *input, char c, int i)
{
	while (input[i] != '\0')
	{
		if (input[i] == c)
			return (i);
		i++;
	}
	return (i);
}

/*busca primero al principio del prompt si encuentra un pipe
y devuelve el error si encuentra unas comillas, avanza hasta
su corresponiente comilla de cierre,
ya que un pipe dentro de comillas es imprimible
y no es un delimitador, si despues encuentra un pipe,
analiza el siguiente char, si es final del string
o es otro pipe, devuelve un error
si la funcion no ha salido por ningun error
y ha encontrado un pipe lo contabilizara
y devuelve la cantidad de pipes
no puedo hacer la verificacion de si hay mas de un pipe
que devuelva error pq me pasaria de lineas...*/
int	find_pipes(char *input)
{
	int	i;

	i = 0;
	if (input && input[0] == '|')
	{
		ft_msn(ERR_PIPE, 2);
		return (1);
	}
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '"')
			i = end_quote(input, input[i], i + 1);
		if (input[i] == '|' && (input[i + 1] == '|' || input[i + 1] == '\0'))
		{
			ft_msn(ERR_PIPE, 2);
			return (1);
		}
		i++;
	}
	return (0);
}

/*funcion que busca la siguiente comilla del mismo tipo que quote_type.
se utiliza *i+1 porque *i ya esta sobre la primera comilla
y se pasa como puntero para hacer avanzar el contador a la funcion find_quotes*/
int	find_pair_quote(char *input, int *i, char quote_type)
{
	int	n;

	n = 1;
	while (input[*i + 1] && input[*i + 1] != quote_type)
		(*i)++;
	if (input[*i + 1] == quote_type)
		n++;
	(*i)++;
	return (n);
}

/*recorre el prompt y cuando encuentra una comilla (sea del tipo que sea)
busca su respectiva comilla de cierre, si no la encuentra la variable squote
o dquote quedara impar y por tanto tendremos un dquote que sacamos como error
Se respetan comillas impares dentro de otras
ya que el contador i se pasa como puntero */
int	find_quotes(char *input, int squote, int dquote)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
			squote += find_pair_quote(input, &i, input[i]);
		else if (input[i] == '"')
			dquote += find_pair_quote(input, &i, input[i]);
		if (squote % 2 != 0)
		{
			ft_msn(ERR_SQUOTE, 1);
			return (1);
		}
		else if (dquote % 2 != 0)
		{
			ft_msn(ERR_DQUOTE, 2);
			return (1);
		}
		i++;
	}
	return (0);
}

/*1 - Comprueba que exista input y seguidamente quita los espacios por delante
y por detras el input con ft_strtrim.
2 - Busca que haya comillas bien cerradas, ya sean dobles o simples.
3 - Busca que no haya pipes ni al principio ni al final de input, pero si
acepta pipes en medio pero las que esten dentro de comillas no las detecte
como pipes, sino como texto plano*/
int	ft_parser(t_data *data)
{
	if (find_quotes(data->prompt, 0, 0) == 1
		|| find_pipes(data->prompt) == 1
		|| find_others(data->prompt) == 1
		|| find_not_allowed(data->prompt) == 1)
	{
		data->rt_value = 2;
		return (1);
	}
	return (0);
}
