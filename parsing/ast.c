/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:40:58 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/23 10:24:49 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_pth	pth;

	init_vars_ast(&pth, tokens);
	while (pth.cur_token != NULL)
	{
		if (pth.cur_token->op == OPEN)
		{
			handle_token_op(&pth, msh);
		}
		else if (pth.cur_token->op == CLOSE)
			return (pth.root);
		else if (is_op_token(pth.cur_token))
		{
			pth.root = handle_operator_ast(&pth.cur_token, pth.root, msh);
			if (!pth.root)
				return (free_ast_return_null(pth.cur_node));
			if (pth.root->right)
				pth.cur_node = pth.root->right;
		}
		else
			handle_nop_block(&pth.cur_token, &pth.cur_node, &pth.root);
	}
	return (pth.root);
}

void	init_vars_ast(t_pth *pth, t_token *tokens)
{
	pth->root = NULL;
	pth->cur_node = NULL;
	pth->cur_token = tokens;
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
