/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ast_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:33:38 by fibarros          #+#    #+#             */
/*   Updated: 2024/07/04 14:05:22 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast *handle_operator_pipe_ast(t_token **current_token, t_ast *root)
{
	t_ast *pipe_node;

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

/*
 * Function to handle operator tokens and update the AST.
 * Takes the current token and the root of the AST as arguments.
 * Returns the updated root of the AST.
 */
t_ast	*handle_operator_ast(t_token **current_token, t_ast *root)
{
	if (current_token && *current_token && (*current_token)->op == PIPE)
		return (handle_operator_pipe_ast(current_token, root));
	else
		return (NULL);
}

int	is_operator(const char *value)
{
	return (valid_op(value) != NONE);
}
