/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:35:09 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/19 16:42:57 by keramos-         ###   ########.fr       */
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
	int		err_code;

	if (root->op != PIPE)
	{
		execute_ast(root, msh);
		return ;
	}
	if (pipe(pipefd) == -1)
		ft_error("pipe");
	if (root->left->op == REDIR_HERE_DOC)
		pipe_heredoc(root->left, msh);
	p1 = fork_first_child(root, msh, pipefd);
	p2 = fork_second_child(root, msh, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(p1, NULL, 0);
	waitpid(p2, &err_code, 0);
	msh->exit_status = WEXITSTATUS(err_code);
	return ;
}

/*
 * Function to fork the first child process.
 */
pid_t	fork_first_child(t_ast *root, t_msh *msh, int pipefd[2])
{
	pid_t	p1;
	int		fd;

	p1 = fork();
	if (p1 == -1)
		ft_error("fork p1");
	if (p1 == 0)
	{
		if (root->left->op == REDIR_HERE_DOC)
		{
			fd = open("tmp_file", O_RDONLY);
			if (fd == -1)
				ft_error("open tmp_file");
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
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

void pipe_heredoc(t_ast *root, t_msh *msh)
{
	int fd;

	fd = open_tmp_file(msh);  // Open a temporary file to store heredoc content
	if (fd == -1)
		return ;

	// Parse and write heredoc content to the temporary file
	if (parse_heredoc(root->redir->here_doc_delim, fd, msh))
	{
		if (g_signal == 2)
			msh->exit_status = 130;
		else
			msh->exit_status = 1;
		close(fd);
		return ;
	}
	close(fd);
}
