/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 23:27:18 by mirifern          #+#    #+#             */
/*   Updated: 2024/08/13 23:27:20 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_execute(t_data *data)
{
    /*int i;

    i = 0;
    if (data->tokens[i])
    {
        printf("*%s\n", data->tokens[i]->value);
        //make_echo(data->tokens, &data);
        i++;
    }*/
    
    
    printf("****\n");
    print_tokens(data);
    make_exit(data->tokens, data);
    //make_echo(data->tokens);
}

