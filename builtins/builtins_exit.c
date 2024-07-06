/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/07/06 19:22:04 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	make_builtins(char **str)
{
	if else(ft_strcmp("echo", str[0], 4) == 1)//with option -n
		make_echo(str);
	if else(ft_strcmp("cd", str[0], 2) == 1)// with only relative or absolute path
		make_cd(str);
	if else(ft_strcmp("pwd", str[0], 3) == 1) // no options
		make_pwd(str);
	if else(ft_strcmp("export", str[0], 6) == 1) // no options
		make_export(str);
	if else(ft_strcmp("unset", str[0], 5) == 1) // no options
		make_unset(str);
	if else(ft_strcmp("env", str[0], 3) == 1) // no option, no args
		make_env(str);
	if else(ft_strcmp("exit", str[0], 4) == 1) // no options
		make_exit(str);
	return ;	
}



void	make_exit(char **str)
{
	int num;
	
	if (!str[1] || str[1] == "0") // si juste exit sans rien apres (si quelque chose avant, a gerer comme une commande avant)
	{
		write(2, "exit\n", 5);
		//fonction final_free
		exit (0);
	}
	if else (!(str[2])) // si 2 args
	{
		if (ft_atoi(str[1]) != 0) // est un nombre
		{
			num = ft_atoi(str[1]);
			if (num < 0)
				modulo_negatif(num);
			if (num > 255)
				num = num % 256;
			write(2, "exit\n", 5);
			//fonction final_free
			exit (num);
		}
		else
		{
			write(2, "exit\n", 5);
			write(2, "" )
			
			//fonction final_free
			exit (2);
		}
		
	}
	
	
	
}