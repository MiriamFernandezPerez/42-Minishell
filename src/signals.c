/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:38:07 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/10 23:44:16 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Global Variable
int	signal_num = 0;

/*Funcion que maneja SIGINT en readline, printa un salto de linea, borra la
linea actual, prepara un nuevo prompt y redibuja el prompt*/
void	readline_sigint_handler(int signum)
{
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_signal_num = 128 + signum;
}

/*Manejador para SIGQUIT durante readline*/
void	readline_sigquit_handler(int signum)
{
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \b\b", STDOUT_FILENO);
	g_signal_num = 128 + signum;
}