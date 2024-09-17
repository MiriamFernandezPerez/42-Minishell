/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 23:27:18 by mirifern          #+#    #+#             */
/*   Updated: 2024/09/17 17:32:31 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Funcion para liberar las secciones*/
/*void	ft_free_sections(t_section **sections, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(sections[i]->tokens);
		free(sections[i]);
		i++;
	}
	free(sections);
}*/

/*anade el token a la seccion a la que pertenece*/
void	add_token_to_section(t_section *section, t_tokens *token)
{
	section->tokens[section->tokens_qt++] = token;
}

/*Crea una seccion nueva por cada pipe*/
t_section	*create_section(int tokens_qt)
{
	t_section	*section;

	section = malloc(sizeof(t_section));
	if (!section)
		exit (EXIT_FAILURE);
	section->tokens = malloc(sizeof(t_tokens *) * tokens_qt);
	if (!section->tokens)
		exit (EXIT_FAILURE);
	section->tokens_qt = 0;
	return (section);
}

/*Detecta pipes si hubiera y separada cada bloque de codigo en secciones*/
t_section	**split_into_sections(t_data *data, int i)
{
	t_section	**sections;
	t_section	*current_section;

	sections = malloc(sizeof(t_section *) * data->tokens_qt);
	if (!sections)
		exit(EXIT_FAILURE);
	current_section = create_section(data->tokens_qt);
	while (++i < data->tokens_qt)
	{
		if (data->tokens[i]->type == PIPE)
		{
			sections[data->sections_qt++] = current_section;
			current_section = create_section(data->tokens_qt);
		}
		else
			add_token_to_section(current_section, data->tokens[i]);
	}
	if (current_section->tokens_qt > 0)
		sections[data->sections_qt++] = current_section;
	else
	{
		free(current_section->tokens);
		free(current_section);
	}
	return (sections);
}

/*Funcion que llama a la que separa el input en secciones cuando
encuentra una pipe*/
void	ft_sections(t_data *data)
{
	data->sections = split_into_sections(data, 0);
	print_sections(data);
}
