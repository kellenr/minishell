/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:40:58 by keramos-          #+#    #+#             */
/*   Updated: 2024/07/05 20:02:12 by keramos-         ###   ########.fr       */
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
	if (!redir) {
		ft_error("init_redir: malloc failed");
		return (NULL);
	}
	redir->input_file = NULL;
	redir->output_file = NULL;
	redir->append_file = NULL;
	redir->here_doc_delim = NULL;
	return (redir);
}

/*
 * Function to initialize an AST node.
 * Takes a pointer to the current token as an argument.
 * Returns a pointer to the newly initialized AST node.
 *
 * Explanation:
 * - Memory Allocation: Allocates memory for a new node.
 * - Default Initialization: Initializes the fields of the node to default values.
 * - Command Initialization: If the current token is a command (not an operator), sets the command field and initializes the args array with the command as the first argument.
 */
t_ast *init_ast(t_token **current_token)
{
	t_ast *node;

	node = malloc(sizeof(t_ast));
	if (!node)
		ft_error("init_ast: malloc failed");
	node->command = NULL;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	node->op = NONE;
	node->redir = NULL;
	if (*current_token && (*current_token)->op == NONE)
	{
		node->command = safe_strdup((*current_token)->value);
		node->args = malloc(sizeof(char *) * (MAX_ARGUMENTS + 1));
		if (!node->args)
			ft_error("init_ast: malloc failed");
		node->args[0] = safe_strdup((*current_token)->value);
		node->args[1] = NULL;
	}
	if (*current_token)
	{
		node->command = safe_strdup((*current_token)->value);
		(*current_token) = (*current_token)->next;
	}
	return (node);
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
	int argc;

	if (current_node->command == NULL)
	{
		current_node->command = safe_strdup((*current_token)->value);
		current_node->args = malloc(sizeof(char *) * (MAX_ARGUMENTS + 1));
		if (!current_node->args)
			ft_error("handle_non_operator: malloc failed");
		current_node->args[0] = safe_strdup((*current_token)->value);
		current_node->args[1] = NULL;
	}
	else
	{
		argc = 0;
		while(current_node->args[argc] != NULL && argc < MAX_ARGUMENTS)
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

/*
 * Function to parse tokens into an AST.
 * Takes the head of the token list as an argument.
 * Returns the root of the AST.
 *
 * If the current token is an operator, handle it
 * in the future we can manage here the other kind of operators
 * like AND, OR, SEMICOLON, REDICTION, etc.
 */
t_ast	*parse_tokens_to_ast(t_token *tokens)
{
	t_ast	*root;
	t_ast	*current_node;
	t_token	*current_token;

	root 			= NULL;
	current_node 	= NULL;
	current_token 	= tokens;
	while (current_token != NULL)
	{
		if (current_token->op == PIPE)
		{
			root = handle_operator_ast(&current_token, root);
			current_node = root->right;
		}
		else if (current_token->op == REDIR_APPEND || current_token->op == REDIR_REPLACE || \
				current_token->op == REDIR_HERE_DOC || current_token->op == REDIR_INPUT)
		{
			root = handle_operator_ast(&current_token, root);
			current_node = root->right;
		}
		else
		{
			if (root == NULL)
			{
				root = init_ast(&current_token);
				current_node = root;
			}
			else if (current_node->command == NULL)
				current_node = handle_non_operator(&current_token, current_node);
			else
				current_node = handle_non_operator(&current_token, current_node);
		}
	}
	return (root);
}
