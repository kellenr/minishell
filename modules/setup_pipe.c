/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:35:09 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/14 13:54:49 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to execute the command on both sides of the pipe.
 * Takes the command structure and the pipe file descriptor as arguments.
 */
void	execute_pipe(t_ast *root, t_msh *msh)
{
	int		pipefd[2];
	pid_t	p1;
	pid_t	p2;

	if (pipe(pipefd) == -1)
		ft_error("pipe");

	if ((p1 = fork()) == -1)
		ft_error("fork p1");
	if (p1 == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_ast(root->left, msh);
		exit(msh->exit_status);
	}
	if ((p2 = fork()) == -1)
		ft_error("fork p2");
	if (p2 == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_ast(root->right, msh);
		exit(msh->exit_status);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(p1, NULL, 0);
	waitpid(p2, NULL, 0);
	return ;
}
