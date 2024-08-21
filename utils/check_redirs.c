/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:11:16 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/21 23:46:08 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if the input file exists.
 *
 * This function checks if the input file specified in the given AST node exists.
 * If the file does not exist, it prints an error message and sets the
 * exit status of the minishell to 1.
 *
 * @param root The root of the AST.
 * @param msh The minishell structure.
 * @return true if the input file exists, false otherwise.
 */
bool	check_input_file(t_ast *root, t_msh *msh)
{
	t_ast	*tmp;

	tmp = root;
	while (tmp)
	{
		if (tmp->op == REDIR_INPUT
			&& (access(tmp->redir->input_file, F_OK) == -1))
		{
			prt_error("No such file or directory\n", tmp->redir->input_file);
			msh->exit_status = 1;
			return (false);
		}
		tmp = tmp->left;
	}
	return (true);
}

/**
 * Checks if the redirection has a command.
 *
 * This function checks if the given AST tree has a command associated with it.
 * If the AST tree does not have a command, it sets the exit status to 0 and
 * closes any file descriptors associated with redirection.
 *
 * @param root The root of the AST tree.
 * @param msh The minishell structure.
 * @return true if the AST tree has a command, false otherwise.
 */
bool	check_redir_has_command(t_ast *root, t_msh *msh)
{
	t_ast	*tmp;
	int		tmpfd;

	tmp = root;
	while (tmp->left)
		tmp = tmp->left;
	if (!tmp->command)
	{
		msh->exit_status = 0;
		tmp = root;
		while (tmp)
		{
			if (tmp->op == REDIR_APPEND || tmp->op == REDIR_REPLACE)
				M_HANDLE_REDIRECTION_FILE(tmp, tmpfd);
			tmp = tmp->left;
		}
		return (false);
	}
	return (true);
}

/**
 * Handles multiple redirection files in the given AST.
 *
 * This function creates the files involved in a redirection operation, specially
 * when there are multiple redirections.
 *
 * @param root The root node of the AST.
 */
void	handle_multiple_redir_files(t_ast *root)
{
	t_ast	*tmp;
	int		tmpfd;

	tmp = root;
	while (tmp->left && (tmp->left->op == tmp->op
			|| tmp->op == REDIR_APPEND || tmp->op == REDIR_REPLACE))
	{
		M_HANDLE_REDIRECTION_FILE(tmp, tmpfd);
		tmp = tmp->left;
	}
}
