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


void ft_add_tokens(t_data *d, char *input, int add_tokens, int pos)
{
    t_tokens    **new_tokens;    // Nuevo array de tokens (estructura)
    char        **split_tokens;      // Array con los tokens generados tras la expansión
    int         i;
    int         j;
    int          k;

    i = 0;
    j = 0;
    k = 0;
    // Divide la entrada expandida (input) en tokens
    split_tokens = ft_split(input, ' '); // Asumiendo que tienes ft_split o similar
   
    // Crear un nuevo array de estructuras t_tokens
    new_tokens = (t_tokens **)malloc(sizeof(t_tokens *) * ((d->tokens_qt + add_tokens) + 1)); // +1 para NULL
    if (!new_tokens)
        ft_malloc(d, NULL, NULL);
    
    // Copiar los tokens anteriores hasta la posición 'pos'
    while (i < pos)
    {
        new_tokens[j] = (t_tokens *)malloc(sizeof(t_tokens));
        if (!new_tokens[j])
            ft_malloc(d, NULL, NULL); // Manejar error si falla la memoria
        // Copiamos tanto el value como el type
        new_tokens[j]->value = ft_strdup(d->tokens[i]->value);
        new_tokens[j]->type = d->tokens[i]->type;
        i++;
        j++;
    }

    // Insertar los nuevos tokens expandidos
    while (split_tokens[k]) {
        new_tokens[j] = (t_tokens *)malloc(sizeof(t_tokens));
        if (!new_tokens[j])
            ft_malloc(d, NULL, NULL);
        // Copiamos el valor del token expandido y asignamos su tipo
        new_tokens[j]->value = ft_strdup(split_tokens[k]);
        new_tokens[j]->type = CMD;  // Aquí asumo que el tipo de los nuevos tokens es ARG (puedes cambiarlo si es necesario)
        k++;
        j++;
    }

    // Copiar el resto de los tokens después de 'pos'
    i = pos + 1; // Saltamos el token original que estamos reemplazando
    while (i < d->tokens_qt) {
        new_tokens[j] = (t_tokens *)malloc(sizeof(t_tokens));
        if (!new_tokens[j])
            ft_malloc(d, NULL, NULL); // Manejar error si falla la memoria
        // Copiamos tanto el value como el type de los tokens originales
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
}


/*Funcion que checkea si depues de expandir hay algun espacio dentro del token*/
void    check_var_spaces(t_data *data, char *input, int pos)
{
    int i;
    int add_tokens;

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