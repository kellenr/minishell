/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:05:15 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/05 13:46:21 by fibarros         ###   ########.fr       */
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
// // Signal handler for the main shell (interactive mode)

// void	sig_handler_int(int signum, siginfo_t *info, void *context)
// {
// 	t_msh	*msh;

// 	(void)info;
// 	msh = (t_msh *)context;
// 	if (signum == SIGINT)
// 	{
// 		printf("\n");
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 		msh->exit_status = 130;
// 	}
// }

// // Setup signal handlers for the main shell

// void	handle_signals(t_msh *msh)
// {
// 	struct sigaction	sa;

// 	sa.sa_sigaction = sig_handler_int;
// 	sa.sa_flags = SA_SIGINFO;
// 	sigemptyset(&sa.sa_mask);
// 	sigaction(SIGINT, &sa, NULL);
// 	sa.sa_handler = SIG_IGN;
// 	sa.sa_flags = 0;
// 	sigaction(SIGQUIT, &sa, NULL);
// 	(void)msh;
// }

// // Signal handler for child processes
// void	sig_handler_child(int signum, siginfo_t *info, void *context)
// {
// 	t_msh	*msh;

// 	msh = (t_msh *)context;
// 	(void)context;
// 	(void)info;
// 	if (signum == SIGINT)
// 	{
// 		msh->exit_status = 130;
// 		ft_putstr_fd("\n", 1);
// 	}
// 	if (signum == SIGQUIT)
// 	{
// 		msh->exit_status = 131;
// 		ft_putstr_fd("Quit (core dumped) \n", 1);
// 	}
// 	ft_putstr_fd("\n", 1);
// }
// // Setup signal handlers for child processes

// void	handle_signals_children(t_msh *msh)
// {
// 	struct sigaction	sa;

// 	sa.sa_sigaction = sig_handler_child;
// 	sa.sa_flags = SA_SIGINFO;
// 	sigemptyset(&sa.sa_mask);
// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGQUIT, &sa, NULL);
// 	(void)msh;
// }

// // Signal handler for heredoc mode
// void	heredoc_sig_handler(int signum, siginfo_t *info, void *context)
// {
// 	(void)info;
// 	(void)context;
// 	if (signum == SIGINT)
// 	{
// 		unlink("tmp_file");
// 		exit(130);
// 	}
// 	else if (signum == SIGQUIT)
// 	{
// 		unlink("tmp_file");
// 		exit(131);
// 	}
// }

// void	handle_signals_heredoc(void)
// {
// 	struct sigaction	sa;

// 	sa.sa_sigaction = heredoc_sig_handler;
// 	sa.sa_flags = SA_SIGINFO;
// 	sigemptyset(&sa.sa_mask);
// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGQUIT, &sa, NULL);
// }
