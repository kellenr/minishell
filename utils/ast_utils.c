/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:06:43 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/15 14:08:02 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*init_ast_node(void)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		ft_error("init_ast: malloc failed");
	node->command = NULL;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	node->op = NONE;
	node->redir = NULL;
	return (node);
}

void	initialize_command_and_args(t_ast *node, t_token *token)
{
	node->command = safe_strdup((token)->value);
	if (!node->command)
		ft_error("malloc error");
	node->args = malloc(sizeof(char *) * (MAX_ARGUMENTS + 1));
	if (!node->args)
	{
		free(node->command);
		ft_error("handle_non_operator: malloc failed");
	}
	node->args[0] = safe_strdup((token)->value);
	if (!node->args[0])
	{
		free(node->command);
		free(node->args);
		ft_error("malloc error");
	}
	node->args[1] = NULL;
}

bool	is_op_token(t_token *token)
{
	if (token->op == PIPE || token->op == AND || token->op == OR || \
	token->op == REDIR_APPEND || token->op == REDIR_REPLACE || \
	token->op == REDIR_HERE_DOC || token->op == REDIR_INPUT)
		return (true);
	return (false);
}

t_ast	*process_token(t_token **token, t_ast *root, t_ast *current_node)
{
	if (root == NULL)
	{
		root = init_ast(token);
		if (!root)
			return (NULL);
		current_node = root;
	}
	else if (current_node->command == NULL)
	{
		current_node = handle_non_operator(token, current_node);
		if (!current_node)
			return (NULL);
	}
	else
	{
		current_node = handle_non_operator(token, current_node);
		if (!current_node)
			return (NULL);
	}
	return (current_node);
}

void	handle_redir_file(t_token **current_token, char **file_field)
{
	*file_field = ft_strdup((*current_token)->value);
	if (!*file_field)
	{
		perror("Memory allocation failed");
		return ;
	}
	(*current_token) = (*current_token)->next;
}
