/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:37:49 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/19 12:16:03 by fibarros         ###   ########.fr       */
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
	if (root->op == REDIR_INPUT)
		handle_input_redir(root, msh);
	else if (root->op == REDIR_REPLACE)
		handle_output_replace(root, msh);
	else if (root->op == REDIR_APPEND)
		handle_output_append(root, msh);
	else if (root->op == REDIR_HERE_DOC)
		handle_heredoc(root, msh);
}

/**
 * Function to handle input redirection.
 *
 * It opens the input file and saves the STDIN_FILENO into a saved_stdin
 * variable. Then it duplicates the input file descriptor into the STDIN_FILENO.
 * After the command is executed, it restores the STDIN_FILENO to
 * the saved_stdin.
*/
t_ast	*create_redir_node(int op, t_ast *root)
{
	t_ast	*redir_node;

	redir_node = malloc(sizeof(t_ast));
	if (!redir_node)
	{
		ft_error("malloc failed");
		return (NULL);
	}
	redir_node->op = op;
	redir_node->left = root;
	redir_node->right = NULL;
	redir_node->command = NULL;
	redir_node->args = NULL;
	redir_node->redir = init_redir();
	if (!redir_node->redir)
	{
		free(redir_node);
		return (NULL);
	}
	return (redir_node);
}

t_ast	*free_redir_node(t_redir *redir, t_ast *node)
{
	free_redir(redir);
	free(node);
	return (NULL);
}
