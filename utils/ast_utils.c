/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:06:43 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/06 10:20:07 by fibarros         ###   ########.fr       */
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
	node->args = malloc(sizeof(char *) * (MAX_ARGUMENTS + 1));
	if (!node->args)
		ft_error("handle_non_operator: malloc failed");
	node->args[0] = safe_strdup((token)->value);
	node->args[1] = NULL;
}
