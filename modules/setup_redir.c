/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:37:49 by keramos-          #+#    #+#             */
/*   Updated: 2024/07/17 11:55:13 by fibarros         ###   ########.fr       */
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

