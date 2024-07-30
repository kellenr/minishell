/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:05:15 by fibarros          #+#    #+#             */
/*   Updated: 2024/07/30 15:57:16 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_int(int signum, siginfo_t *info, void *context)
{
	t_msh	*msh;

	msh = (t_msh *)context;
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		msh->exit_status = 130;
	}
}

void	handle_signals(t_msh *msh)
{
	struct sigaction	sa;

	sa.sa_sigaction = sig_handler_int;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (isatty(STDIN_FILENO))
	{
		sigaction(SIGINT, &sa, NULL);
		sa.sa_sigaction = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
}

void	sig_handler_child(int signum, siginfo_t *info, void *context)
{
	t_msh	*msh;

	msh = (t_msh *)context;
	if (signum == SIGINT)
	{
		msh->exit_status = 130;
		ft_putstr_fd("\n", 1);
	}
	if (signum == SIGQUIT)
	{
		msh->exit_status = 131;
		ft_putstr_fd("Quit (core dumped) \n", 1);
	}
}

void	handle_signals_children(t_msh *msh)
{
	struct sigaction	sa;

	sa.sa_sigaction = sig_handler_child;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	heredoc_sig_handler(int signum, siginfo_t *info, void *context)
{
	t_msh	*msh;

	msh = (t_msh *)context;
	if (signum == SIGINT)
	{
		unlink("tmp_file");
		exit(130);
	}
	else if (signum == SIGQUIT)
	{
		unlink("tmp_file");
		exit(signum == 131);
	}
}
