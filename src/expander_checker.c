/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 21:42:18 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/19 04:24:26 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_tokens(t_data *d, char *input, int add_tokens, int pos)
{
	t_tokens	**new_tokens;
	char		**split_tokens;
	int			j;

	split_tokens = ft_split(input, ' ');
	new_tokens = init_new_tok(d, add_tokens);
	j = copy_tok_before(d, new_tokens, pos);
	j = insert_exp_tok(d, new_tokens, split_tokens, j);
	j = copy_rest_tok(d, new_tokens, pos, j);
	final_tok(d, new_tokens, j, split_tokens);
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

int	check_previous_null(t_data *d, int i, char *cpy, char *expanded)
{
	if (verify_previous_type(d, i, cpy) == 1)
		return (1);
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
	return (0);
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

int	expand_check_and_prev(t_data *d, char *cpy, char *expanded, int *i)
{
	cpy = ft_strdup(d->tokens[*i]->value);
	free(d->tokens[*i]->value);
	expanded = expand_env_variables(d, cpy, NULL);
	d->tokens[*i]->value = expanded;
	check_var_spaces(d, d->tokens[*i]->value, *i);
	if (!d->tokens[*i]->value[0])
	{
		if (check_previous_null(d, *i, cpy, expanded) == 1)
			return (1);
	}
	else
	{
		d->tokens[*i]->type = ARG;
		free(cpy);
	}
	return (0);
}
