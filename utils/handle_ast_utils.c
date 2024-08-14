/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ast_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:23:54 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/12 16:01:12 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redir_input(t_token **current_token, t_ast *redir_node)
{
	if (redir_node->op == REDIR_INPUT)
	{
		handle_redir_file(current_token, &redir_node->redir->input_file);
		if (!redir_node->redir->input_file)
		{
			free_redir_node(redir_node->redir, redir_node);
			return (1);
		}
		return (0);
	}
	return (1);
}

int	handle_redir_replace(t_token **current_token, t_ast *redir_node)
{
	if (redir_node->op == REDIR_REPLACE)
	{
		handle_redir_file(current_token, &redir_node->redir->output_file);
		if (!redir_node->redir->output_file)
		{
			free_redir_node(redir_node->redir, redir_node);
			return (1);
		}
		return (0);
	}
	return (1);
}

int	handle_redir_append(t_token **current_token, t_ast *redir_node)
{
	if (redir_node->op == REDIR_APPEND)
	{
		handle_redir_file(current_token, &redir_node->redir->append_file);
		if (!redir_node->redir->append_file)
		{
			free_redir_node(redir_node->redir, redir_node);
			return (1);
		}
		return (0);
	}
	return (1);
}

int	handle_redir_heredoc(t_token **current_token, t_ast *redir_node)
{
	if (redir_node->op == REDIR_HERE_DOC)
	{
		handle_redir_file(current_token, &redir_node->redir->here_doc_delim);
		if (!redir_node->redir->here_doc_delim)
		{
			free_redir_node(redir_node->redir, redir_node);
			return (1);
		}
		return (0);
	}
	return (1);
}
