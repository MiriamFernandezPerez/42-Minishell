/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/07/10 20:20:25 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*void	make_builtins(char **str, char **env) // en faire un deuxieme pour qund je recois une simple string comme echo?
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
	long long int num;
	
	if (!str[1] || (ft_strncmp(str[1], "0", 1) == 0 && !str[2])) // si juste exit (ou exit 0)
	{
		write(2, "exit\n", 5);
		//fonction final_free
		exit (0);
	}
	if (str[1]) // si 2 args et plus
	{
		if (check_minmax(str[1]) == 0) // est un nombre
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
	char *argv[3];
	
	argv[0] = "exit";
	argv[1] = "-9223372036854775";
	//argv[2]	= "-520";
	argv[2]	= '\0';
	make_exit(argv);
	return(0);
}*/

void	make_echo(char **str) // avec char null a la fin
{
	if (str[1])
		write(1, str[1], ft_strlen(str[1]));//verifier les STDIN/ERROR des write
	if (ft_strncmp(str[0], "echo -n", 7) != 0)
		write(1, "\n", 1);
	return;
}

/*int main() // test echo
{
	char *str[2];
	
	str[0] = "echo -n";
	//str[1] = "hola que tal?";
	str[1] = '\0';
	make_echo(str);
	return(0);
}*/

void	adjust_env(int j, char **env)
{
	int i;
	
	i = 0;
	while (env[i])
		i++;
	while (j < i)
	{
		env[j] = env[j + 1];
		j++;
	}
	//printf("%s\n", env[23]);
	//free(env[j]);
	return ;
}

void	make_unset(char **str, char **env)
{
	int i;
	int j;

	i = 2; // mettre 2 pour le test avec le main sinon 1
	while (str[i]) //check si on n'est pas en read only? ok env sans
	{
		j = 0;
		while (env[j])
		{
			//printf("%d = ", ft_strncmp(str[i], env[j], ft_strlen(str[i])));
			//printf("%s\n", env[j]);
			if (ft_strncmp(str[i], env[j], ft_strlen(str[i]) != 0))
				j++;
			else
			{
				//free(getenv(env[j])); //la valeur
				//env[j] = NULL;
				//free(env[j]); //le nom
				adjust_env(j, env);//rearanger les autres lignes pour ne pas avoir de trous
				break;
			}
		}
		i++; // passer a l'argument suivant si il y a
	}
	write (1, "\n", 1);
	return ;
}

int main(int argc, char **argv, char **env) // test unset
{
	(void)argc;

	make_unset(argv, env);
	return(0);
}