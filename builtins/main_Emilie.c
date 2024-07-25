/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_Emilie.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/07/25 16:50:31 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv, char **env)
{
	
	char	*str[4];
	t_data	*data;
	//t_env	*current;
	(void)argc;
	//(void)argv;
	data = NULL;
	str[0]= argv[1];
	str[1]= argv[2];
	str[2]= argv[3];
	str[3]= '\0';
	ft_initialize(&data, env);
	make_cd(str, data);
	make_env(data);
	/*current = data->env_lst;
	while (current)
	{
		printf("%s=%s FLAG=%d\n", current->name, current->value, current->flag);
		current = current->next;
	}*/
	final_free(data);
	return (0);
}
//verifier avec un nom _test si dans l'export et l'env

//ATTENTION Miriam envoie les args separes de la cmd, changer les fonctions comme ca