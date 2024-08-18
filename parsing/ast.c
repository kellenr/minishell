/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:40:58 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/18 03:37:38 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to initialize a redirection structure.
 * Returns a pointer to the newly initialized redirection structure.
 */
t_redir	*init_redir(void)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
	{
		perror("init_redir: malloc failed");
		return (NULL);
	}
	redir->input_file = NULL;
	redir->output_file = NULL;
	redir->append_file = NULL;
	redir->here_doc_delim = NULL;
	return (redir);
}

/*
 * Function to parse tokens into an AST.
 * Takes the head of the token list as an argument.
 * Returns the root of the AST.
 *
 * If the current token is an operator, handle it
 * in the future we can manage here the other kind of operators
 * like AND, OR, SEMICOLON, REDICTION, etc.
 */
t_ast	*parse_tokens_to_ast(t_token *tokens, t_msh *msh)
{
	t_ast	*root;
	t_ast	*cur_node;
	t_token	*cur_token;
	t_ast	*pthesis_node;

	root = NULL;
	cur_node = NULL;
	cur_token = tokens;
	while (cur_token != NULL)
	{
		if (cur_token->op == OPEN)
			handle_token_op(&cur_token, &cur_node, &root, &pthesis_node, msh);
		else if (cur_token->op == CLOSE)
			return (root);
		else if (is_op_token(cur_token))
		{
			root = handle_operator_ast(&cur_token, root, msh);
			if (!root)
				return (free_ast_return_null(cur_node));
			if (root->right)
				cur_node = root->right;
		}
		else
			handle_nop_block(&cur_token, &cur_node, &root);
	}
	return (root);
}

/*
 * Function to create a new AST node.
 * Returns a pointer to the newly created AST node.
 */
t_ast	*create_ast_node(void)
{
	t_ast	*node;

	node = init_ast_node();
	if (!node)
	{
		perror("malloc fail");
		return (NULL);
	}
	node->command = NULL;
	node->args = NULL;
	return (node);
}

/*
 * Function to initialize an AST node.
 * Returns a pointer to the newly initialized AST node.
 */
int	set_command_and_args(t_ast *node, t_token *current_token)
{
	node->command = safe_strdup(current_token->value);
	if (!node->command)
		return (handle_malloc_failure(node, "malloc failed for command"));
	node->args = malloc(sizeof(char *) * (MAX_ARGUMENTS + 1));
	if (!node->args)
	{
		free(node->command);
		free(node);
		perror("malloc failed for args");
		return (-1);
	}
	node->args[0] = safe_strdup(current_token->value);
	if (!node->args[0])
	{
		free(node->args);
		free(node->command);
		free(node);
		perror("malloc failed for args");
		return (-1);
	}
	node->args[1] = NULL;
	return (0);
}

/*
 * Function to initialize an AST node.
 * Returns a pointer to the newly initialized AST node.
 */
t_ast	*init_ast(t_token **current_token)
{
	t_ast	*node;

	node = create_ast_node();
	if (!node)
		return (NULL);
	if (*current_token && (*current_token)->op == NONE)
	{
		if (set_command_and_args(node, *current_token) == -1)
			return (NULL);
	}
	if (*current_token)
		(*current_token) = (*current_token)->next;
	return (node);
}
