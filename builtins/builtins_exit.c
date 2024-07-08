/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/07/08 21:40:38 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*void	make_builtins(char **str) // en faire un deuxieme pour qund je recois une simple string comme echo?
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
}*/



void	make_exit(char **str) // attention AVEC '\0'a la fin de l'array
{
	int num;
	
	if (!str[1] || (ft_strncmp(str[1], "0", 1) == 0 && !str[2])) // si juste exit (ou exit 0)
	{
		write(2, "exit\n", 5);
		//fonction final_free
		exit (0);
	}
	if (str[1]) // si 2 args et plus
	{
		if (ft_atoi(str[1]) != 0 || ft_strncmp(str[1], "0", 1) == 0) // est un nombre
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
				write(2, "exit\n👯 minishell> : exit: too many arguments", 47); // a valider avec le prompt car ne doit pas sortir du programme
		}
		else
		{
			write(2, "exit\n👯 minishell> : exit: ", 29);
			write(2, &(*str[1]), ft_strlen(str[1]));
			write(2, ": numeric argument required\n", 28);			
			//fonction final_free
			exit (2);
		}
		
	}
}

/*int main() // test exit
{
	char *argv[4];
	
	argv[0] = "exit";
	argv[1] = "0";
	argv[2]	= "-520";
	argv[3]	= '\0';
	make_exit(argv);
	return(0);
}*/

void	make_echo(char *str) // avec char null a la fin
{
	write(1, str, ft_strlen(str));//verifier les STDIN/ERROR des write
	write(1, "\n", 1);
	return;
}

/*int main() // test echo
{
	char *str = "hola que tal?";
	
	make_echo(str);
	return(0);
}*/