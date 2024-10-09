/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 22:38:07 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/09 22:38:09 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Global Variable
int	signal_num = 0;

/*Funcion que maneja SIGINT en readline, printa un salto de linea, borra la
linea actual, prepara un nuevo prompt y redibuja el prompt*/
void    readline_sigint_handler(int signum)
{
    printf("\n");
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    signal_num = 128 + signum;
}

/*Manejador vacio para SIGQUIT durante readline*/
void    readline_sigquit_handler(int signum)
{
    rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \b\b", STDOUT_FILENO);
    signal_num = 128 + signum; 
}

void    exe_sigquit_handler(int signum)
{
    ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
    signal_num = 128 + signum;
}

void    exe_sigint_handler(int signum)
{
    ft_putstr_fd("\n", STDOUT_FILENO);
    rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \b\b", STDOUT_FILENO);
    signal_num = 128 + signum;
}

/*Manejo de senales en ejecucion, pongo las senales por default*/
void    set_execution_signals() {
    struct sigaction sa_int;
    struct sigaction sa_quit;

    sa_int.sa_handler = exe_sigint_handler;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);

    sa_quit.sa_handler = exe_sigquit_handler;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);
}

void    set_readline_signals()
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    sa_int.sa_handler = readline_sigint_handler;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);

    sa_quit.sa_handler = readline_sigquit_handler;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);
}