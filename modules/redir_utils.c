/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 11:18:57 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/20 14:07:03 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_input_redir(t_ast *root, t_msh *msh)
{
	int	fd;

	if (root->redir->input_file == NULL || access(root->redir->input_file, \
		F_OK) == -1)
	{
		prt_error("msh: %s: No such file or directory\n", \
		root->redir->input_file);
		msh->exit_status = 1;
		return ;
	}
	fd = open(root->redir->input_file, O_RDONLY, 0);
	if (fd == -1)
	{
		prt_error("msh: %s: No such file or directory\n", root->redir->input_file);
		msh->exit_status = 1;
		return ;
	}
	redirect_and_execute(fd, STDIN_FILENO, root, msh);
}

void	handle_output_replace(t_ast *root, t_msh *msh)
{
	int	fd;

	fd = open(root->redir->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		prt_error("msh: %s: No such file or directory\n", root->redir->output_file);
		msh->exit_status = 1;
		return ;
	}
	redirect_and_execute(fd, STDOUT_FILENO, root, msh);
}

void	handle_output_append(t_ast *root, t_msh *msh)
{
	int	fd;

	fd = open(root->redir->append_file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		prt_error("msh: %s: No such file or directory\n", root->redir->append_file);
		msh->exit_status = 1;
		return ;
	}
	redirect_and_execute(fd, STDOUT_FILENO, root, msh);
}

int	handle_fd_redirection(int fd, int target_fd)
{
	int	saved_fd;

	saved_fd = dup(target_fd);
	if (saved_fd == -1)
	{
		perror("dup");
		close(fd);
		//close(saved_fd);
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

void	redirect_and_execute(int fd, int std_fd, t_ast *root, t_msh *msh)
{
	int	saved_fd;
	int	tmpfd;

	t_ast *tmp = root;
	while (tmp->left)
		tmp = tmp->left;
	if (!tmp->command)
	{
		msh->exit_status = 0;
		tmp = root;
		while (tmp)
		{
			if (tmp->op == REDIR_APPEND || tmp->op == REDIR_REPLACE)
			{
				if (tmp->op == REDIR_APPEND)
					tmpfd = open(tmp->redir->append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
				else
					tmpfd = open(tmp->redir->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				close(tmpfd);
			}
			tmp = tmp->left;
		}
		return ;
	}
	saved_fd = handle_fd_redirection(fd, std_fd);
	if (saved_fd == -1)
	{
		msh->exit_status = 1;
		return ;
	}
	if (root)
		tmp = root;
	while (tmp->left && (tmp->left->op == tmp->op || tmp->op == REDIR_APPEND || tmp->op == REDIR_REPLACE))
	{
		if (tmp->op == REDIR_APPEND)
			tmpfd = open(tmp->redir->append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			tmpfd = open(tmp->redir->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		tmp = tmp->left;
		close(tmpfd);
	}
	while (root->left && (root->left->op == root->op || root->left->op == REDIR_REPLACE || root->left->op == REDIR_APPEND))
		root = root->left;
	execute_ast(root->left, msh);
	dup2(saved_fd, std_fd);
	close(saved_fd);
}
