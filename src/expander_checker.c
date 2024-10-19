/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:42:18 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/16 21:42:20 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*void	ft_add_tokens(t_data *d, char *input, int add_tokens, int pos)
{
	t_tokens	**new_tokens;
	char		**split_tokens;
	int			i;
	int			j;
	int			k;

	i = 0;
	j = 0;
	k = 0;
	split_tokens = ft_split(input, ' ');
	new_tokens = (t_tokens **)malloc(sizeof(t_tokens *)
			* ((d->tokens_qt + add_tokens) + 1));
	if (!new_tokens)
		ft_malloc(d, NULL, NULL);
	//inserto los rokens hasta encontrar el expandido
	while (i < pos)
	{
		new_tokens[j] = (t_tokens *)malloc(sizeof(t_tokens));
		if (!new_tokens[j])
			ft_malloc(d, NULL, NULL);
		new_tokens[j]->value = ft_strdup(d->tokens[i]->value);
		new_tokens[j]->type = d->tokens[i]->type;
		i++;
		j++;
	}
	// Insertar los nuevos tokens expandidos
	while (split_tokens[k])
	{
		new_tokens[j] = (t_tokens *)malloc(sizeof(t_tokens));
		if (!new_tokens[j])
			ft_malloc(d, NULL, NULL);
		new_tokens[j]->value = ft_strdup(split_tokens[k]);
		new_tokens[j]->type = CMD;
		k++;
		j++;
	}
	// Copiar el resto de los tokens después de 'pos'
	i = pos + 1;
	while (i < d->tokens_qt)
	{
		new_tokens[j] = (t_tokens *)malloc(sizeof(t_tokens));
		if (!new_tokens[j])
			ft_malloc(d, NULL, NULL);
		new_tokens[j]->value = ft_strdup(d->tokens[i]->value);
		new_tokens[j]->type = d->tokens[i]->type;
		i++;
		j++;
	}
	// Asegurarse de que el nuevo array termine con NULL
	new_tokens[j] = NULL;
	// Liberar el array original de tokens
	ft_free(d->tokens);
	// Actualizar el array de tokens y la cantidad de tokens en la estructura
	d->tokens = new_tokens;
	d->tokens_qt = d->tokens_qt + add_tokens;
	free_array(split_tokens);
}*/

t_tokens **ft_init_new_tokens(t_data *d, int add_tokens)
{
	t_tokens **new_tokens;

	new_tokens = (t_tokens **)malloc(sizeof(t_tokens *) 
		* (d->tokens_qt + add_tokens + 1));
	if (!new_tokens)
		ft_malloc(d, NULL, NULL);
	return new_tokens;
}


int ft_copy_tokens_until(t_data *d, t_tokens **new_tokens, int pos)
{
	int i = 0;
	int j = 0;

	while (i < pos)
	{
		new_tokens[j] = (t_tokens *)malloc(sizeof(t_tokens));
		if (!new_tokens[j])
			ft_malloc(d, NULL, NULL);
		new_tokens[j]->value = ft_strdup(d->tokens[i]->value);
		new_tokens[j]->type = d->tokens[i]->type;
		i++;
		j++;
	}
	return j;
}


int ft_insert_expanded_tokens(t_data *d, t_tokens **new_tokens, char **split_tokens, int j)
{
	int k = 0;

	while (split_tokens[k])
	{
		new_tokens[j] = (t_tokens *)malloc(sizeof(t_tokens));
		if (!new_tokens[j])
			ft_malloc(d, NULL, NULL);
		new_tokens[j]->value = ft_strdup(split_tokens[k]);
		new_tokens[j]->type = CMD;
		k++;
		j++;
	}
	return j;
}


int ft_copy_remaining_tokens(t_data *d, t_tokens **new_tokens, int pos, int j)
{
	int i = pos + 1;

	while (i < d->tokens_qt)
	{
		new_tokens[j] = (t_tokens *)malloc(sizeof(t_tokens));
		if (!new_tokens[j])
			ft_malloc(d, NULL, NULL);
		new_tokens[j]->value = ft_strdup(d->tokens[i]->value);
		new_tokens[j]->type = d->tokens[i]->type;
		i++;
		j++;
	}
	return j;
}


void ft_finalize_tokens(t_data *d, t_tokens **new_tokens, int total_tokens, char **split_tokens)
{
	new_tokens[total_tokens] = NULL;
	ft_free(d->tokens);
	d->tokens = new_tokens;
	d->tokens_qt = total_tokens;
	free_array(split_tokens);
}


void ft_add_tokens(t_data *d, char *input, int add_tokens, int pos)
{
	t_tokens **new_tokens;
	char **split_tokens;
	int j;

	split_tokens = ft_split(input, ' ');
	new_tokens = ft_init_new_tokens(d, add_tokens);
	j = ft_copy_tokens_until(d, new_tokens, pos);
	j = ft_insert_expanded_tokens(d, new_tokens, split_tokens, j);
	j = ft_copy_remaining_tokens(d, new_tokens, pos, j);
	ft_finalize_tokens(d, new_tokens, j, split_tokens);
}


/*Funcion que checkea si depues de expandir hay algun espacio dentro del token*/
void	check_var_spaces(t_data *data, char *input, int pos)
{
	int	i;
	int	add_tokens;

	i = 0;
	add_tokens = 0;
	(void) data;
	while (input[i] != '\0')
	{
		if (ft_isspace(input[i]))
			add_tokens++;
		i++;
	}
	if (add_tokens != 0)
		ft_add_tokens(data, input, add_tokens, pos);
}

void	check_previous_null(t_data *d, int i, char *cpy, char *expanded)
{
	if (verify_previous_type(d, i, cpy) == 1)
		return ;
	else if (verify_previous_type(d, i, cpy) == 2)
	{
		d->tokens[i]->type = ARG;
		d->tokens[i]->value = cpy;
		free(expanded);
	}
	else
	{
		d->tokens[i]->type = END;
		free(cpy);
	}
}

int	check_previous_heredoc(t_data *d, int i)
{
	if (i == 0)
		return (0);
	if (d->tokens[i - 1] && d->tokens[i - 1]->type == SPACES)
	{
		if (d->tokens[i - 2] && d->tokens[i - 2]->type == HEREDOC)
			return (1);
	}
	else if (d->tokens[i - 1] && d->tokens[i - 1]->type == HEREDOC)
		return (1);
	return (0);
}