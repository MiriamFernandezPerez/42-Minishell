/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 23:27:18 by mirifern          #+#    #+#             */
/*   Updated: 2024/08/16 18:49:39 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_token_to_section(t_section *section, t_tokens *token) {
	section->tokens[section->tokens_qt++] = token;
}

t_section *create_section(int tokens_qt) {
	t_section *section;

	section = malloc(sizeof(t_section));
	section->tokens = malloc(sizeof(t_tokens *) * tokens_qt);
	section->tokens_qt = 0;
	return (section);
}

t_section **split_into_sections(t_data *data) {
	int			i;
	t_section	**sections;
	t_section	*current_section;

	i = 0;
	sections = malloc(sizeof(t_section *) * data->tokens_qt);
	data->sections_qt = 0;
	current_section = create_section(data->tokens_qt);
	while (i < data->tokens_qt) {
		if (data->tokens[i]->type == PIPE) {
			sections[data->sections_qt++] = current_section;
			current_section = create_section(data->tokens_qt);
		} else {
			add_token_to_section(current_section, data->tokens[i]);
		}
		i++;
	}

	// Agregar la última sección si no está vacía
	if (current_section->tokens_qt > 0) {
		sections[data->sections_qt++] = current_section;
	} else {
		free(current_section->tokens);
		free(current_section);
	}

	return sections;
}

void ft_sections(t_data *data)
{
	data->sections = split_into_sections(data);
	for (int i = 0; i < data->sections_qt; i++) {
		free(data->sections[i]->tokens);
		free(data->sections[i]);
	}
	free(data->sections);
	free(data->tokens);
}

// Función de prueba para imprimir las secciones
void print_sections(t_data *data) {
	for (int i = 0; i < data->sections_qt; i++) {
		printf("SECCION %d:\n", i + 1);
		for (int j = 0; j < data->sections[i]->tokens_qt; j++) {
			printf("  Token %d: %s (Type: %d)\n", j, data->sections[i]->tokens[j]->value, data->sections[i]->tokens[j]->type);
		}
	}
}
