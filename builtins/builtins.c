/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:17:55 by esellier          #+#    #+#             */
/*   Updated: 2024/07/12 21:37:28 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*int	make_builtins(char **str, t_env **env_lst) // en faire un deuxieme pour qund je recois une simple string comme echo?
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
			return (127); // pour pas que l'environnement s'ouvre si deja unset path
		make_unset(str);
	}
	else if(ft_strcmp("env", str[0], 3) == 1) // no option, no args
		make_env(env_lst);
	else if(ft_strcmp("exit", str[0], 4) == 1) // no options
		make_exit(str);
	return (0);	
}*/

void	exit_number(char **str)
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
		exit (num);
	}
	else
		write(2, "exit\n👯 minishell> : exit: too many arguments", 47);
		// a valider avec le prompt car ne doit pas sortir du programme
		//echo $? == 1, comment faire? ne fonctionne pas avec un return
	return ;
}


void	make_exit(char **str) // attention AVEC '\0'a la fin de l'array
{
	if (!str[1] || (ft_strncmp(str[1], "0", 1) == 0 && !str[2])) // si juste exit (ou exit 0)
	{
		write(2, "exit\n", 5);
		//fonction final_free
		exit (0);
	}
	if (str[1]) // si 2 args et plus
	{
		if (check_minmax(str[1]) == 0) // est un nombre
			exit_number(str);
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

void	make_env(t_env **env_lst)
{
	t_env	*current;
	
	current = (*env_lst);
	while(current)
	{
		printf("%s", current->name);
        printf("%s\n", current->value);
		current = current->next;
	}
	//retour prompt
	return ;
}

/*int main(int argc, char **argv, char **env) //env
{
	(void)argc;
	(void)argv;
	t_env **env_lst;
	t_env	*tmp;

	env_lst = create_env(env);
	make_env(env_lst);
	while(*env_lst)
	{
		tmp = *env_lst;
		free((*env_lst)->name);
		free((*env_lst)->value);
		(*env_lst) = (*env_lst)->next;
		free (tmp);
	}
	free (env_lst);
    return(0);
}*/