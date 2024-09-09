/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/09/09 16:53:42 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_builtins(char **str, t_data *data) //checker avec un pipe et autres args ensuite
{
	if (ft_strcmp("echo", str[0]) == 0)//with option -n
		make_echo(str);
	if (ft_strcmp("cd", str[0]) == 0)// with only relative or absolute path
		make_cd(str, data);
	if (ft_strcmp("pwd", str[0]) == 0)
		make_pwd(data);
	if (ft_strcmp("export", str[0]) == 0)
		make_export(str, data);
	if (ft_strcmp("unset", str[0]) == 0)
		make_unset(str, data);
	if (ft_strcmp("env", str[0]) == 0)
		make_env(data, str);
	if (ft_strcmp("exit", str[0]) == 0)
		make_exit(str, data);
	else // peut etre pas necessaire si type dans la structure, on vient aue si builtins
		return(2); //pour pas confondre avec un erreur de malloc
	if (make_cd == 1 || make_export == 1 || make_pwd == 1 || make_env == 1
		|| make_exit == 1)
		return (data->rt_value = 1, 1); // voir comment gerer l'erreur dans l'exe (on stop et retourne le prompt?)
	return (data->rt_value = 0, 0);
}

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
		ft_free_data(data);
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
	if (!str[1] || (ft_strncmp(str[1], "0", 1) == 0 && !str[2])) //1 arg
	{
		write(2, "exit\n", 5);
		ft_free_data(data);
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
			ft_free_data(data);
			exit (2);
		}
	}
	return (0);
}

void	make_echo(char **str)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	while (str[i])
	{
		if (ft_strncmp(str[i], "-n", ft_strlen(str[i])) == 0)
			flag = 1;
		else
			break ;
		i++;
	}
	while (str[i])
	{
		write (1, str[i], ft_strlen(str[i]));
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
	return ;
}

int	make_pwd(t_data *data)
{
	char	*buf;

	buf = ft_calloc(1, 256 * sizeof(char));
	if (!buf)
		ft_malloc(data, NULL, NULL);
	if (getcwd(buf, 256) == 0)
	{
		write(2, "cannot find current directory\n", 30);
		return (free(buf), 1);
	}
	else
		printf("%s\n", buf);
	return (free(buf), 0);
}
//getcwd = fonction qui recupere l'adresse actuelle (fonctionne si unset PWD)
