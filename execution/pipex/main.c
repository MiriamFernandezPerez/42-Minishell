/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:33:18 by esellier          #+#    #+#             */
/*   Updated: 2024/09/10 15:39:45 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "libft/libft.h"

t_args	*structure(void)
{
	t_args	*args;

	args = (t_args *)malloc(sizeof(t_args));
	if (!args)
	{
		write(2, "Structure error\n", 16);
		exit(1);
	}
	args->path = NULL;
	args->cmd = NULL;
	args->array = NULL;
	args->flag = 0;
	args->pid1 = 5;
	args->pid2 = 5;
	return (args);
}

char	*check_file(char *file, t_args *args, char **env, char **argv)
{
	int	j;

	j = 0;
	if (file == argv[1] && (access(file, R_OK) != 0 || access(file, F_OK) != 0))
	{
		if (access(file, F_OK) == 0 && access(file, R_OK) != 0)
			write (2, "Infile error: Permission denied\n", 32);
		if (access(file, F_OK) != 0)
			write (2, "Infile error: No such file or directory\n", 40);
		j = -1;
	}
	if (file == argv[1])
		return (search_path(env, j, 1, argv));
	if ((file == argv[4]) && ((access(file, F_OK) == 0
				&& access(file, W_OK) != 0) || (access(file, F_OK) != 0
				&& ft_strncmp(file, "\0", 1) == 0)))
	{
		if (access(file, F_OK) == 0 && access(file, W_OK) != 0)
			write (2, "Outfile error: Permission denied\n", 33);
		if (access(file, F_OK) != 0 && ft_strncmp(file, "\0", 1) == 0)
			write (2, "Outfile error: No such file or directory\n", 41);
		args->flag = 1;
		return (NULL);
	}
	return (search_path(env, j, 0, argv));
}

int	first_check(t_args *args, int argc, char **argv, char **env)
{
	char	*temp;

	if (argc != 5 || ft_strncmp(argv[1], "\"", 1) == 0
		|| ft_strncmp(argv[4], "\"", 1) == 0)
	{
		write(2, "Expected: infile command 1 command 2 outfile\n", 45);
		exit (1);
	}
	temp = check_file(argv[1], args, env, argv);
	if (temp)
		args->array = split_env(temp);
	if (access(argv[1], F_OK | R_OK) != 0)
		return (1);
	args->cmd = check_args(argv[2], 1, args, argv);
	if (!args->cmd && ft_strncmp(argv[2], "/", 1) != 0)
		write (2, "First command: Permission denied\n", 33);
	if (args->cmd == NULL)
		return (0);
	if (args->array)
		args->path = check_path(args->array, args->cmd[0], 1, argv[1]);
	return (0);
}

int	final_free(t_args *args)
{
	int	status1;
	int	status2;
	int	r;

	r = args->flag;
	close (args->fd[0]);
	if (args->path)
		free (args->path);
	if (args->cmd)
		free_array (args->cmd);
	if (args->array)
		free_array (args->array);
	waitpid(args->pid1, &status1, 0);
	waitpid(args->pid2, &status2, 0);
	if (args)
		free (args);
	if (r == 1)
		return (r);
	return (status2);
}

int	main(int argc, char **argv, char **env)
{
	t_args	*args;

	args = structure();
	first_check(args, argc, argv, env);
	create_pipe(args->fd, args);
	if (args->cmd != NULL)
		create_in_child(args, argv[1], env);
	if (args->path)
		free (args->path);
	args->path = NULL;
	if (args->cmd)
		free_array (args->cmd);
	args->cmd = NULL;
	check_file(argv[4], args, env, argv);
	if (access(argv[4], W_OK) == 0 || access(argv[4], F_OK) != 0)
		args->cmd = check_args(argv[3], 0, args, argv);
	if (args->cmd == NULL && argv[4][0] && (access(argv[4], W_OK) == 0
		|| access(argv[4], F_OK) != 0))
		cmd_errors(argv);
	if (args->cmd != NULL && argv[4][0] && (access(argv[4], W_OK) == 0
			|| access(argv[4], F_OK) != 0))
		args->path = check_path(args->array, args->cmd[0], 0, argv[4]);
	close (args->fd[1]);
	create_out_child(args, argv[4], env);
	return (final_free (args));
}
