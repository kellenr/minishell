/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:18:57 by fibarros          #+#    #+#             */
/*   Updated: 2024/07/15 12:54:37 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_input_redir(t_ast *root, t_msh *msh)
{
	int	fd;
	int	saved_stdin;

	fd = open(root->redir->input_file, O_RDONLY, 0);
	if (fd == -1)
	{
		ft_printf("msh: %s, no such file or directory\n", \
		root->redir->input_file);
		msh->exit_status = 1;
		return ;
	}
	saved_stdin = handle_fd_redirection(fd, STDIN_FILENO);
	if (saved_stdin == -1)
	{
		msh->exit_status = 1;
		return ;
	}
	execute_ast(root->left, msh);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}

void	handle_output_replace(t_ast *root, t_msh *msh)
{
	int	fd;
	int	saved_stdout;

	fd = open(root->redir->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("open");
		msh->exit_status = 1;
		return ;
	}
	saved_stdout = handle_fd_redirection(fd, STDOUT_FILENO);
	if (saved_stdout == -1)
	{
		msh->exit_status = 1;
		return ;
	}
	execute_ast(root->left, STDOUT_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}

void	handle_output_append(t_ast *root, t_msh *msh)
{
	int	fd;
	int	saved_stdout;

	fd = open(root->redir->append_file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("open");
		msh->exit_status = 1;
		return ;
	}
	saved_stdout = handle_fd_redirection(fd, STDOUT_FILENO);
	if (saved_stdout == -1)
	{
		msh->exit_status = 1;
		return ;
	}
	execute_ast(root->left, STDOUT_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}

int	handle_fd_redirection(int fd, int target_fd)
{
	int	saved_fd;

	saved_fd = dup(target_fd);
	if (saved_fd == -1)
	{
		perror("dup");
		close(fd);
		close(saved_fd);
		return (-1);
	}
	if (dup2(fd, target_fd) == -1)
	{
		perror("dup2");
		close(fd);
		close(saved_fd);
		return (-1);
	}
	close(fd);
	return (saved_fd);
}
