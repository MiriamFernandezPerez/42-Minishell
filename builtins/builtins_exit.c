/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/07/06 20:33:14 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	make_builtins(char **str)
{
	if (ft_strcmp("echo", str[0], 4) == 1)//with option -n
		make_echo(str);
	else if(ft_strcmp("cd", str[0], 2) == 1)// with only relative or absolute path
		make_cd(str);
	else if(ft_strcmp("pwd", str[0], 3) == 1) // no options
		make_pwd(str);
	else if(ft_strcmp("export", str[0], 6) == 1) // no options
		make_export(str);
	else if(ft_strcmp("unset", str[0], 5) == 1) // no options
		make_unset(str);
	else if(ft_strcmp("env", str[0], 3) == 1) // no option, no args
		make_env(str);
	else if(ft_strcmp("exit", str[0], 4) == 1) // no options
		make_exit(str);
	return ;	
}



void	make_exit(char **str) // attention pas de '\0'a la fin de l'array dans cette version
{
	int num;
	
	if (!str[1] || str[1] == "0") // si juste exit (ou exit 0) sans rien apres (si quelque chose avant, a gerer comme une commande avant)
	{
		write(2, "exit\n", 5);
		//fonction final_free
		exit (0);
	}
	if (str[1]) // si 2 args et plus
	{
		if (ft_atoi(str[1]) != 0) // est un nombre
		{
			num = ft_atoi(str[1]);
			if (!str[2])
			{
				if (num < 0)
					num = modulo_negativ(num);
				if (num > 255)
					num = num % 256;
				write(2, "exit\n", 5);
				//fonction final_free
				exit (num);
			}
			else
				write(2, "exit\n👯 minishell> : exit: too many arguments", 47); //verifier le compte
		}
		else
		{
			write(2, "exit\n👯 minishell> : exit: ", 26); //compte a verifier
			write(2, &str[1], ft_strlen(str[1]));
			write(2, ": numeric argument required\n", 28);			
			//fonction final_free
			exit (2);
		}
		
	}
	/*if (str[2]) // si plus de 2 args
	{
		if (str[1] == a un nombre ok)//faire ici
			write(2, "exit\n👯 minishell> : exit: too many arguments", 47); //verifier le compte
		else
		{
			write(2, "exit\n", 5);
			write(2, "👯 minishell> : exit: ", 21); //compte a verifier
			write(2, &str[1], ft_strlen(str[1]));
			write(2, ": numeric argument required\n", 28);
			//fonction final_free
			exit (2);
			//a combiner avec l'option au de deux args.
		}
	}*/
}