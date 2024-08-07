/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:05:15 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/05 16:46:13 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_int(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 1;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler_int);
}

void	sig_non_interactive(int signum)
{
	if (signum == SIGQUIT)
		ft_printf("Quit (core dumped)");
	write(1, "\n", STDERR_FILENO);
	rl_on_new_line();
}

void	handle_non_interactive(void)
{
	signal(SIGINT, sig_non_interactive);
	signal(SIGQUIT, sig_non_interactive);
}

void	sig_handle_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 2;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
	if (signum == SIGQUIT)
		return ;
}
