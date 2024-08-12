/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:48:01 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/12 04:13:00 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_token_op(t_token **cur_token, t_ast **cur_node, t_ast **root, \
t_ast **pthesis_node)
{
	*pthesis_node = handle_parentheses_ast(cur_token, *root);
	if (!(*root))
	{
		*root = *pthesis_node;
		*cur_node = *root;
	}
	else
	{
		(*cur_node)->right = *pthesis_node;
		(*cur_node) = (*cur_node)->right;
	}
}

void	*free_ast_return_null(t_ast *cur_node)
{
	free_ast(cur_node);
	return (NULL);
}

void	*handle_nop_block(t_token **cur_token, t_ast **cur_node, t_ast **root)
{
	if (*root == NULL)
	{
		*root = init_ast(cur_token);
		if (!(*root))
			return (free_ast_return_null(*cur_node));
		*cur_node = *root;
	}
	else if ((*cur_node)->command == NULL)
	{
		*cur_node = handle_non_operator(cur_token, *cur_node);
		if (!cur_node)
			return (free_ast_return_null(*root));
	}
	else
	{
		*cur_node = handle_non_operator(cur_token, *cur_node);
		if (!cur_node)
			return (free_ast_return_null(*root));
	}
	return (cur_node);
}

int	handle_malloc_failure(t_ast *node, const char *error_message)
{
	free(node);
	perror(error_message);
	return (-1);
}
