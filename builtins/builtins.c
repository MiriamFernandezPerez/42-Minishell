/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/07/26 20:40:59 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*int	make_builtins(char **str, t_data *data) //checker avec un pipe et autres args ensuite
{
	if (ft_strcmp("echo", str[0], 4) == 1)//with option -n
		make_echo(str);
	if (ft_strcmp("cd", str[0], 2) == 1)// with only relative or absolute path
		make_cd(str, t_data *data);
	if (ft_strcmp("pwd", str[0], 3) == 1)
		make_pwd(void);
	if (ft_strcmp("export", str[0], 6) == 1)
		make_export(str);
	if (ft_strcmp("unset", str[0], 5) == 1)
		make_unset(str, data);
	if (ft_strcmp("env", str[0], 3) == 1)
		make_env(data, str);
	if (ft_strcmp("exit", str[0], 4) == 1)
		make_exit(str, data);
	else // peut etre pas necessaire si type dans la structure, on vient aue si builtins
		return(2); //pour pas confondre avec un erreur de malloc
	if (make_cd == 1 || make_export == 1 || make_pwd == 1 || make_env == 1
		|| make_exit == 1)
		return (data->rt_value = 1, 1); // voir comment gerer l'erreur dans l'exe (on stop et retourne le prompt?)
	return (data->rt_value = 0, 0);
}*/
//si n,entre pas ici cherche dans l'array du path si la commande existe, avant l'exe
 // unset retourne tjr 0 et prend tous les args sauf -l... 
 //(a manager pour tous car pas d'options pour les builtins
 
int	exit_number(char **str, t_data *data)
{
	long long	num;

	num = ft_atoi(str[1]);
	if (!str[2])
	{
		if (num < 0)
			num = modulo_negativ(num);
		if (num > 255)
			num = num % 256;
		write(2, "exit\n", 5);
		//data->rt_value = num; // pas necessaire si on free derriere ?
		final_free(data);
		exit (num);
	}
	else
	{
		write(2, "exit\n👯 minishell> : exit: too many arguments", 47);
		// a valider avec le prompt car ne doit pas sortir du programme
		return (data->rt_value = 1, 1);
	}
	return (0);
}

int	make_exit(char **str, t_data *data)
{
	if (!str[1] || (ft_strncmp(str[1], "0", 1) == 0 && !str[2]))//1 arg
	{
		write(2, "exit\n", 5);
		final_free(data);
		exit (0);
	}
	if (str[1]) // si 2 args et plus
	{
		if (check_minmax(str[1]) == 0) // est un nombre
		{
			if (exit_number(str, data) == 1)
			return (1);
		}
		else
		{
			write(2, "exit\n👯 minishell> : exit: ", 29);
			write(2, &(*str[1]), ft_strlen(str[1]));
			write(2, ": numeric argument required\n", 28);
			final_free(data);
			exit (2);
		}
	}
	return (0);
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

void	make_echo(char **str) // avec char null a la fin
{
	if (str[1])
		write (1, str[1], ft_strlen(str[1]));
	if (ft_strncmp(str[0], "echo -n", 7) != 0)
		write(1, "\n", 1);
	return ;
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

/*void	make_pwd(t_data *data)
{
	t_env	*current;

	current = data->env_lst;
	while (ft_strcmp(current->name, "PWD") != 0)
		current = current->next;
	if (ft_strcmp(current->name, "PWD") == 0)
		printf("%s\n", current->value);
	data->rt_value = 0;
	return ;
}*/

int	make_pwd(void)
{
	char	*buf;

	buf = ft_calloc(1, 256 * sizeof(char));
	if (!buf)
		return (1);
	if (getcwd(buf, 256) == 0)
	{
		printf("cannot find current directory\n");
		return (free(buf), 1);
	}
	else
		printf("%s\n", buf);
	return (free(buf), 0);
}
//getcwd = fonction qui recupere l'adresse actuelle (fonctionne si unset PWD)
