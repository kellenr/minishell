/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ast_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:33:38 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/18 00:14:59 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*handle_operator_pipe_ast(t_token **current_token, t_ast *root)
{
	t_ast	*pipe_node;

	if (root == NULL)
	{
		prt_error("msh: syntax error near unexpected token '|'\n", NULL);
		return (NULL);
	}
	pipe_node = malloc(sizeof(t_ast));
	if (!pipe_node)
		ft_error("malloc failed");
	pipe_node->op = PIPE;
	pipe_node->left = root;
	pipe_node->right = NULL;
	pipe_node->command = NULL;
	pipe_node->args = NULL;
	pipe_node->redir = NULL;
	(*current_token) = (*current_token)->next;
	pipe_node->right = init_ast(current_token);
	if (!pipe_node->right)
	{
		free(pipe_node);
		return (NULL);
	}
	return (pipe_node);
}

t_ast	*handle_operator_redir_ast(t_token **current_token, t_ast *root)
{
	t_ast	*redir_node;

	redir_node = create_redir_node((*current_token)->op, root);
	if (!redir_node)
		return (NULL);
	(*current_token) = (*current_token)->next;
	if (*current_token == NULL || is_operator((*current_token)->op))
	{
		prt_error("msh: syntax error near unexpected token 'newline'\n", NULL);
		return (free_redir_node(redir_node->redir, redir_node));
	}
	if (handle_redir_input(current_token, redir_node) == 0 || \
		handle_redir_replace(current_token, redir_node) == 0 || \
		handle_redir_append(current_token, redir_node) == 0 || \
		handle_redir_heredoc(current_token, redir_node) == 0)
		return (redir_node);
	else
	{
		redir_node->right = init_ast(current_token);
		if (!redir_node->right)
			return (free_redir_node(redir_node->redir, redir_node));
	}
	return (redir_node);
}

t_ast	*handle_operator_and_or_ast(t_token **current_token, t_ast *root)
{
	t_ast	*and_or_node;

	if (root == NULL)
	{
		prt_error("msh: syntax error near unexpected token '%s'\n", \
				(*current_token)->value);
		return (NULL);
	}
	and_or_node = malloc(sizeof(t_ast));
	if (!and_or_node)
	{
		perror("malloc fail");
		return (NULL);
	}
	and_or_node->op = (*current_token)->op;
	and_or_node->left = root;
	and_or_node->right = NULL;
	and_or_node->command = NULL;
	and_or_node->args = NULL;
	and_or_node->redir = NULL;
	(*current_token) = (*current_token)->next;
	and_or_node->right = init_ast(current_token);
	return (and_or_node);
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
		else if ((*current_token)->op == AND || (*current_token)->op == OR)
			return (handle_operator_and_or_ast(current_token, root));
	}
	return (NULL);
}

/*
 * Function to handle non-operator tokens and update the AST.
 * Takes the current token and the current AST node as arguments.
 * Returns the updated current AST node.
 *
 * Add the argument to the command's args
 * current_node->args = realloc(current_node->args, sizeof(char *) * (argc + 2));
 * Error: too many arguments
 * Free the AST and exit
 */
t_ast	*handle_non_operator(t_token **current_token, t_ast *current_node)
{
	int	argc;

	if (current_node->command == NULL)
		initialize_command_and_args(current_node, *current_token);
	else
	{
		argc = 0;
		while (current_node->args[argc] != NULL && argc < MAX_ARGUMENTS)
			argc++;
		if (argc < MAX_ARGUMENTS)
		{
			current_node->args[argc] = safe_strdup((*current_token)->value);
			current_node->args[argc + 1] = NULL;
		}
		else
		{
			free_ast(current_node);
			ft_error("Error: too many arguments");
		}
	}
	(*current_token) = (*current_token)->next;
	return (current_node);
}
