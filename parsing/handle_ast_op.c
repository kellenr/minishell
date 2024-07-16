/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ast_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:33:38 by fibarros          #+#    #+#             */
/*   Updated: 2024/07/16 16:51:29 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*handle_operator_pipe_ast(t_token **current_token, t_ast *root)
{
	t_ast	*pipe_node;

	pipe_node = malloc(sizeof(t_ast));
	if (!pipe_node)
		ft_error("malloc failed");
	pipe_node->op = PIPE;
	pipe_node->left = root;
	pipe_node->right = NULL;
	pipe_node->command = NULL;
	pipe_node->args = NULL;
	(*current_token) = (*current_token)->next;
	pipe_node->right = init_ast(current_token);
	return (pipe_node);
}

t_ast	*handle_operator_redir_ast(t_token **current_token, t_ast *root)
{
	t_ast	*redir_node;

	redir_node = malloc(sizeof(t_ast));
	if (!redir_node)
		ft_error("malloc failed");
	redir_node->op = (*current_token)->op;
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
	(*current_token) = (*current_token)->next;
	if (redir_node->op == REDIR_INPUT)
	{
		redir_node->redir->input_file = ft_strdup((*current_token)->value);
		(*current_token) = (*current_token)->next;
	}
	else if (redir_node->op == REDIR_REPLACE)
	{
		redir_node->redir->output_file = ft_strdup((*current_token)->value);
		(*current_token) = (*current_token)->next;
	}
	else if (redir_node->op == REDIR_APPEND)
	{
		redir_node->redir->append_file = ft_strdup((*current_token)->value);
		(*current_token) = (*current_token)->next;
	}
	else if (redir_node->op == REDIR_HERE_DOC)
	{
		redir_node->redir->here_doc_delim = ft_strdup((*current_token)->value);
		(*current_token) = (*current_token)->next;
	}
	else
		redir_node->right = init_ast(current_token);
	return (redir_node);
}

/*
 * Function to handle operator tokens and update the AST.
 * Takes the current token and the root of the AST as arguments.
 * Returns the updated root of the AST.
 */
t_ast	*handle_operator_ast(t_token **current_token, t_ast *root)
{
	if (current_token && *current_token)
	{
		if ((*current_token)->op == PIPE)
			return (handle_operator_pipe_ast(current_token, root));
		else if ((*current_token)->op == REDIR_APPEND || \
				(*current_token)->op == REDIR_REPLACE || \
				(*current_token)->op == REDIR_HERE_DOC || \
				(*current_token)->op == REDIR_INPUT)
			return ((handle_operator_redir_ast(current_token, root)));
	}
	return (NULL);
}

// void	init_redir_node(t_ast *node, t_token **token, t_ast *root)
// {
// 	node->op = (*token)->op;
// 	node->left = root;
// 	node->right = NULL;
// 	node->command = NULL;
// 	node->args = NULL;
// 	node->redir = init_redir();
// }
