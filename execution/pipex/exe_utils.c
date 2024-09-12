/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:03:19 by esellier          #+#    #+#             */
/*   Updated: 2024/09/12 19:14:16 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **lst_to_array(t_env *lst)
{
    int     i;
    char    **array;
    t_env   *current;

    i = 0;
    current = lst;
    array = (char **)malloc(sizeof (char *));
    while(current) //+ check les flags qui vont dans l'env
    {
        array[i] = malloc((ft_strlen(lst->name) + ft_strlen(lst->value) + 2)* sizeof (char *));
        ft_strlcpy(array[i], lst->name, ft_strlen(lst->name));
        ft_strlcat(array[i], "=", ft_strlen(lst->name));
        ft_strlcat(array[i], lst->value, ft_strlen(lst->name + 1));
    }
    array[i] = '\0';
    return (array);
}