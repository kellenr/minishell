/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:37:49 by keramos-          #+#    #+#             */
/*   Updated: 2024/07/07 16:30:33 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to handle redirections.
 *
 * Its important to notice that this funcion is saving the
 * STDIN_FILENO into a saved_stdin variable because we need
 * to restore it after the redirection is done. Otherwise the
 * next readline call will return NULL because the STDIN is closed.
*/
void	handle_redirection(t_ast *root, t_msh *msh)
{
	int fd;
	int saved_stdin;
	int saved_stdout;

	if (root->op == REDIR_INPUT)
	{
		fd = open(root->redir->input_file, O_RDONLY, 0);
		if (fd == -1)
		{
			ft_printf("msh: %s, no such file or directory\n", root->redir->input_file);
			msh->exit_status = 1;
			return ;
		}
		saved_stdin = dup(STDIN_FILENO);
		if (saved_stdin == -1)
		{
			ft_error("dup");
			msh->exit_status = 1;
			close(fd);
			return ;
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		execute_ast(root->left, msh);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);

	}
	else if (root->op == REDIR_REPLACE)
	{
		fd = open(root->redir->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd == -1)
		{
			perror("open");
			msh->exit_status = 1;
			return;
		}
		saved_stdout = dup(STDOUT_FILENO);
		if (saved_stdout == -1)
		{
			perror("dup");
			msh->exit_status = 1;
			close(fd);
			return;
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		execute_ast(root->left, msh);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	// else if (root->op == REDIR_APPEND)
	// 	fd = open(root->redir->append_file, O_WRONLY | O_APPEND | O_CREAT, 0777);
	// else if (root->op == REDIR_HERE_DOC)
	// 	fd = handle_heredoc(root->redir->here_doc_delim);
	//printf("Redirection handled: op=%d\n", root->op);  // Debug statement

}

// int	handle_heredoc(const char *delimiter)
// {
// }
