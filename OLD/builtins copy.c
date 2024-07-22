/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/07/15 17:57:21 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*int	make_builtins(char **str, t_env **env_lst, t_data *data) // en faire un deuxieme pour qund je recois une simple string comme echo?
{
	if (ft_strcmp("echo", str[0], 4) == 1)//with option -n
		make_echo(str, data);
	else if(ft_strcmp("cd", str[0], 2) == 1)// with only relative or absolute path
		make_cd(str);
	else if(ft_strcmp("pwd", str[0], 3) == 1) // no options
		make_pwd(str);
	else if(ft_strcmp("export", str[0], 6) == 1) // no options
		make_export(str);
	else if(ft_strcmp("unset", str[0], 5) == 1) // no options
	{
		if (check_path(env_lst) == 1) //pas possible de verifier sans le prompt
		{
			data->rt_value = 127; // pour pas que l'environnement s'ouvre si deja unset path
			return (0);
		}
		make_unset(str, env_lst, data);
	}
	else if(ft_strcmp("env", str[0], 3) == 1) // no option, no args
		make_env(env_lst, data);
	else if(ft_strcmp("exit", str[0], 4) == 1) // no options
		make_exit(str, data);
	else
		return(1);
	return (0);	
}*/

void	exit_number(char **str, t_data *data)
{
	long long num;
	
	num = ft_atoi(str[1]);
	if (!str[2])
	{
		if (num < 0)
			num = modulo_negativ(num);
		if (num > 255)
			num = num % 256;
		write(2, "exit\n", 5);
		//fonction final_free
		data->rt_value = num;
		exit (num);
	}
	else
	{
		write(2, "exit\n👯 minishell> : exit: too many arguments", 47);
		// a valider avec le prompt car ne doit pas sortir du programme
		data->rt_value = 1;
	}	
	return ;
}


void	make_exit(char **str, t_data *data)
{
	if (!str[1] || (ft_strncmp(str[1], "0", 1) == 0 && !str[2])) // si juste exit (ou exit 0)
	{
		write(2, "exit\n", 5);
		data->rt_value = 0;
		//fonction final_free
		exit (0);
	}
	if (str[1]) // si 2 args et plus
	{
		if (check_minmax(str[1]) == 0) // est un nombre
			exit_number(str, data);
		/*{
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
				write(2, "exit\n👯 minishell> : exit: too many arguments", 47);
		}*/
		else
		{
			write(2, "exit\n👯 minishell> : exit: ", 29);
			write(2, &(*str[1]), ft_strlen(str[1]));
			write(2, ": numeric argument required\n", 28);	
			//fonction final_free
			data->rt_value = 2;
			exit (2);
		}
	}
}

/*int main() // test exit
{
	char *argv[4];
	
	argv[0] = "exit";
	argv[1] = "-9223372036854775";
	argv[2]	= "-520";
	argv[3]	= '\0';
	make_exit(argv);
	return(0);
}*/

void	make_echo(char **str, t_data *data) // avec char null a la fin
{
	if (str[1])
		write(1, str[1], ft_strlen(str[1]));//verifier les STDIN/ERROR des write
	if (ft_strncmp(str[0], "echo -n", 7) != 0)
		write(1, "\n", 1);
	data->rt_value = 0;
	return;
}

/*int main() // test echo
{
	char *str[3];
	t_data data;
	
	str[0] = "echo -n";
	str[1] = "hola que tal?";
	str[2] = '\0';
	make_echo(str, &data);
	return(0);
}*/

/*void	make_rtvalue(char **str, t_data *data)//no necessary, expander!!
{
	int i;

	i = 2;
	printf("%d\n", data->rt_value);
	while (str[1][i])
	{
		while (str[1][i] == ' ')
			i++;
		if (str[1][i - 1] == ' ')
			write (1, " ",1);
		write(1, &str[1][i], 1);
		i++;
	}
	data->rt_value = 0;
	return ;// OPTION 1 is pas expand
	printf("%s\n", str[1]); //si a l'expand on dit que $? == data->rt_value
	//TRAITER LES ESPACES, seulement un par groupe!
	data->rt_value = 0;
	return ;
}*/

/*int main(int argc, char **argv)
{
	t_data data;
	(void)argc;
	char *print[2];
	
	print[0] = argv[1];
	print[1]= "argv[2]";
	printf("argv[1] = %s\n", argv[1]);
	printf("argv[2] = %s\n", argv[2]);
	printf("argv[3] = %s\n", argv[3]);
	make_rtvalue(print, &data);
	return (0);	
}*/
