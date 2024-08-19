/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:48:01 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/19 12:43:35 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_token_op(t_token **cur_token, t_ast **cur_node, t_ast **root, \
		t_ast **pthesis_node, t_msh *msh)
{
	*pthesis_node = handle_parentheses_ast(cur_token, *root, msh);
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

void	process_heredoc_flag(int *heredoc_flag, t_msh *msh, char *token)
{
	if (*heredoc_flag)
	{
		*heredoc_flag = 0;
		if (has_quotes(token))
			msh->heredoc_flag = 1;
		else
			msh->heredoc_flag = 0;
	}
}
