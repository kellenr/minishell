/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:35:09 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/22 17:09:26 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to execute a pipe command.
 */
void	execute_pipes(t_ast *root, t_msh *msh)
{
	int		pipefd[2];
	pid_t	p1;
	pid_t	p2;
	int		heredoc_fd;

	heredoc_fd = -1;
	if (root->op != PIPE)
	{
		execute_ast(root, msh);
		return ;
	}
	if (pipe(pipefd) == -1)
		ft_error("pipe");
	if (root->left->op == REDIR_HERE_DOC)
	{
		heredoc_fd = handle_heredoc_pipe(root->left, msh);
		if (heredoc_fd == -1)
			ft_error("heredoc_fd");
		p1 = fork_first_child_heredoc(root, msh, pipefd, heredoc_fd);
	}
	else
		p1 = fork_first_child(root, msh, pipefd);
	p2 = fork_second_child(root, msh, pipefd);
	return (wait_for_childs(p1, p2, pipefd, msh));
}

void	wait_for_childs(pid_t p1, pid_t p2, int pipefd[2], t_msh *msh)
{
	int	err_code;

	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(p1, NULL, 0);
	waitpid(p2, &err_code, 0);
	msh->exit_status = WEXITSTATUS(err_code);
}

/*
 * Function to fork the first child process.
 */
pid_t	fork_first_child(t_ast *root, t_msh *msh, int pipefd[2])
{
	pid_t	p1;

	p1 = fork();
	if (p1 == -1)
		ft_error("fork p1");
	if (p1 == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_ast(root->left, msh);
		exit(msh->exit_status);
	}
	return (p1);
}

/*
 * Function to fork the second child process.
 */
pid_t	fork_second_child(t_ast *root, t_msh *msh, int pipefd[2])
{
	pid_t	p2;

	p2 = fork();
	if (p2 == -1)
		ft_error("fork p2");
	if (p2 == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_ast(root->right, msh);
		exit(msh->exit_status);
	}
	return (p2);
}

pid_t	fork_first_child_heredoc(t_ast *root, t_msh *msh, int pipefd[2], \
		int heredoc_fd)
{
	pid_t	p1;
	int		saved_fd;

	p1 = fork();
	if (p1 == -1)
		ft_error("fork p1");
	if (p1 == 0)
	{
		saved_fd = dup(STDIN_FILENO);
		dup2(heredoc_fd, STDIN_FILENO);
		close(heredoc_fd);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_ast(root->left->left, msh);
		dup2(saved_fd, STDIN_FILENO);
		close(saved_fd);
		exit(msh->exit_status);
	}
	return (p1);
}

