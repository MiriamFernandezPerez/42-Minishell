/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_Emilie.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/07/26 23:49:56 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv, char **env)
{
	
	char	**str;
	t_data	*data;
	//t_env	*current;
	int i;
	int	j;

	i = 0;
	j = 1;
	data = NULL;
	str = malloc((argc) * sizeof(char *));
	while (i < argc -1)
	{
		str[i++] = argv[j++];
	}
	str[i] = '\0';
	//printf("str = %s\n", str[3]);
	/*i = 0;
	while (str[i])
	{
		printf ("str = %s\n", str[i]);
		i++;
	}*/
	ft_initialize(&data, env);
	make_export(str, data);
	//make_env(data, str);
	/*current = data->env_lst;
	while (current)
	{
		printf("%s=%s FLAG=%d\n", current->name, current->value, current->flag);
		current = current->next;
	}*/
	free (str);
	final_free(data);
	return (0);
}
//verifier avec un nom _test si dans l'export et l'env

//ATTENTION Miriam envoie les args separes de la cmd, changer les fonctions comme ca