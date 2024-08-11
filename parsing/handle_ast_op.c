/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ast_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:33:38 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/11 18:03:19 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*handle_operator_pipe_ast(t_token **current_token, t_ast *root)
{
	t_ast	*pipe_node;

	if (root == NULL)
	{
		ft_printf("msh: syntax error near unexpected token '|'\n");
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
	if (redir_node->op == REDIR_INPUT)
	{
		handle_redir_file(current_token, &redir_node->redir->input_file);
		if (!redir_node->redir->input_file)
		{
			free_redir(redir_node->redir);
			free(redir_node);
			return (NULL);
		}
	}
	else if (redir_node->op == REDIR_REPLACE)
	{
		handle_redir_file(current_token, &redir_node->redir->output_file);
		if (!redir_node->redir->output_file)
		{
			free_redir(redir_node->redir);
			free(redir_node);
			return (NULL);
		}
	}
	else if (redir_node->op == REDIR_APPEND)
	{
		handle_redir_file(current_token, &redir_node->redir->append_file);
		if (!redir_node->redir->append_file)
		{
			free_redir(redir_node->redir);
			free(redir_node);
			return (NULL);
		}
	}
	else if (redir_node->op == REDIR_HERE_DOC)
	{
		handle_redir_file(current_token, &redir_node->redir->here_doc_delim);
		if (!redir_node->redir->here_doc_delim)
		{
			free_redir(redir_node->redir);
			free(redir_node);
			return (NULL);
		}
	}
	else
	{
		redir_node->right = init_ast(current_token);
		if (!redir_node->right)
		{
			free_redir(redir_node->redir);
			free(redir_node);
			return (NULL);
		}
	}
	return (redir_node);
}

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

t_ast	*handle_operator_and_or_ast(t_token **current_token, t_ast *root)
{
	t_ast	*and_or_node;

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
