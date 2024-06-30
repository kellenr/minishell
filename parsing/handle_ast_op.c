/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ast_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:33:38 by fibarros          #+#    #+#             */
/*   Updated: 2024/07/01 00:24:44 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to create an operator node and update the AST.
 * Returns the new operator node.
 */
t_ast	*create_operator_node(t_token **current_token, t_ast *ast_node)
{
	t_ast	*new_node;

	new_node = create_ast_node((*current_token)->value, (*current_token)->op);
	new_node->left = ast_node;
	*current_token = (*current_token)->next;
	return (new_node);
}

/*
 * Function to handle child nodes and update the AST.
 * Takes the current token as an argument.
 * Returns the right child of the AST.
 */
t_ast	*handle_child(t_token **current_token, t_ast *current_right)
{
	if (current_right->op == NONE && *current_token && (*current_token)->op == NONE)
	{
		current_right->left = create_ast_node((*current_token)->value, \
		(*current_token)->op);
		*current_token = (*current_token)->next;
	}
	return (current_right);
}

/*
 * Function to handle remaining tokens and update the AST.
 * Takes the current token and the right child of the AST as arguments.
 */
void	handle_remaining_tokens(t_token **token, t_ast *right)
{
	t_ast	*arg_node;
	t_ast	*temp;

	while (*token)
	{
		if ((*token)->op != NONE)
		{
			right->right = handle_operator_ast(token, right->right);
			break ;
		}
		else
		{
			arg_node = create_ast_node((*token)->value, (*token)->op);
			if (!right->left)
				right->left = arg_node;
			else
			{
				temp = right->left;
				while (temp->right)
					temp = temp->right;
				temp->right = arg_node;
			}
			*token = (*token)->next;
		}
	}
}

/*
 * Function to handle operator tokens and update the AST.
 * Takes the current token and the root of the AST as arguments.
 * Returns the updated root of the AST.
 */
t_ast	*handle_operator_ast(t_token **current_token, t_ast *root)
{
	t_ast	*new_node;
	t_ast	*current_right;

	new_node = create_operator_node(current_token, root);
	while (*current_token && !is_operator((*current_token)->value))
	{
		new_node->right = create_ast_node((*current_token)->value, (*current_token)->op);
		*current_token = (*current_token)->next;
		if(*current_token && !is_operator((*current_token)->value))
		{
			current_right = new_node->right;
			handle_child(current_token, current_right);
			handle_remaining_tokens(current_token, current_right);
		}
	}
	return (new_node);
}






// t_ast	*handle_operator_ast(t_token **current_token, t_ast *root)
// {
// 	t_ast	*new_node;
// 	t_ast	*current_right;

// 	new_node = create_operator_node(current_token, root);
// 	while (*current_token && !is_operator((*current_token)->value))
// 	{
// 		new_node->right = create_ast_node((*current_token)->value, (*current_token)->op);
// 		*current_token = (*current_token)->next;
// 		current_right = new_node->right;
// 		handle_child(current_token, current_right);
// 		handle_remaining_tokens(current_token, current_right);
// 	}
// 	return (new_node);
// }


// t_ast	*handle_operator_ast(t_token **current_token, t_ast *root)
// {
// 	t_ast	*new_node;
// 	t_ast	*current_right;

// 	new_node = create_operator_node(current_token, root);
// 	while (*current_token && !is_operator((*current_token)->value))
// 	{
// 		new_node->right = create_ast_node((*current_token)->value, (*current_token)->op);
// 		root = new_node;
// 		*current_token = (*current_token)->next;
// 		if (*current_token && !is_operator((*current_token)->value))
// 		{
// 			new_node->right = create_ast_node((*current_token)->value, (*current_token)->op);
// 			current_right = new_node->right;
// 			handle_child(current_token, current_right);
// 			handle_remaining_tokens(current_token, current_right);
// 		}
// 	}
// 	return (root);
// }

int	is_operator(const char *value)
{
    return (valid_op(value) != NONE);
}
