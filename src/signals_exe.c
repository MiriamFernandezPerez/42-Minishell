/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:46:03 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/10 23:46:04 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	exe_sigint_handler(int signum)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	ft_putstr_fd("  \b\b", STDOUT_FILENO);
	signal_num = 128 + signum;
}

void	exe_sigquit_handler(int signum)
{
	ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
	signal_num = 128 + signum;
}

/*Manejo de senales en ejecucion, pongo las senales por default*/
void	set_execution_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = exe_sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = exe_sigquit_handler;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}