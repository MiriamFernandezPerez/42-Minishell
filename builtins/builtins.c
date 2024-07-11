/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/07/11 21:21:52 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*int	make_builtins(char **str, char **env) // en faire un deuxieme pour qund je recois une simple string comme echo?
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
	{
		if (check_path(env_lst) == 1) //pas possible de verifier sans le prompt
			return (127);
		make_unset(str);
	}
	else if(ft_strcmp("env", str[0], 3) == 1) // no option, no args
		make_env(str);
	else if(ft_strcmp("exit", str[0], 4) == 1) // no options
		make_exit(str);
	return (0);	
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

int	check_path(t_env **env_lst)
{
	t_env	*current;

	current = (*env_lst);
	while (current)
	{
		if (ft_strncmp(current->name, "PATH=", 5)== 0)
			return(0);
		current = current->next;
	}
	write(1, "👯 minishell> : env: No such file or directory", 48);
	return (1);
}

t_env	**adjust_env(t_env **env_lst, t_env *to_del)
{
	t_env	*previous;
	t_env	*current;
	
	previous = NULL;
	current = (*env_lst);
	while ((current) != to_del)
	{
		previous = (current);
		(current) = (current)->next;
	}
	free((current)->name);
	free((current)->value);
	if (previous)
		previous->next = (current)->next;
	if (!previous)
		*env_lst = (current)->next;
	free(current);
	return (env_lst);
}

t_env	**make_unset(char **str, t_env **env_lst)
{
	t_env	*current;
	int		i;
	
	i = 1;
	while (str[i]) //check si on n'est pas en read only? ok env sans
	{
		current = (*env_lst);
		while (current)
		{
			if (ft_strncmp(str[i], current->name, ft_strlen(current->name) - 1) == 0)
			{
				env_lst = adjust_env(env_lst, current); //supprimer le node
				current = *env_lst;
			}
			else
				current = current->next;
		}
		i++; // passer a l'argument suivant si il y a
	}
	//write (1, "\n", 1);
	return (env_lst);
}

int main(int argc, char **argv, char **env) //unset
{
	t_env	**envi;
	(void)argc;
	t_env	*current;
	t_env	*to_print;
	
	envi = create_env(env);
	if (check_path(envi) == 1)
			return (127);
	check_path(envi);
	envi = make_unset(argv, envi);
	to_print = (*envi);
	while (to_print)
	{
        printf("%s", to_print->name);
        printf("%s\n", to_print->value);
		to_print = to_print->next;
	}
	while(*envi)
	{
		current = (*envi);
		free(current->name);
		free(current->value);
		(*envi) = current->next;
		free (current);
	}
	free (envi);
    return(0);
}