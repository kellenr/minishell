/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_and_or_parent.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:17:06 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/11 23:04:56 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to handle logical operators in the AST.
 * Takes the root of the AST and the minishell structure as arguments.
 * Executes the left node and then the right node if the condition is met.
 */
void	handle_logical_op(t_ast *root, t_msh *msh)
{
	if (root->op == AND)
	{
		execute_ast(root->left, msh);
		if (msh->exit_status == 0)
			execute_ast(root->right, msh);
	}
	else if (root->op == OR)
	{
		execute_ast(root->left, msh);
		if (msh->exit_status != 0)
			execute_ast(root->right, msh);
	}
}

void	handle_parentheses_op(t_ast *root, t_msh *msh)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		msh->exit_status = 1;
		return ;
	}
	if (pid == 0)
	{
		execute_ast(root, msh);
		exit(msh->exit_status);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		msh->exit_status = WEXITSTATUS(status);
	}
	else
		perror("fork");
}

t_ast	*parse_parentheses(t_token **current_token)
{
	t_ast	*pthesis_node;

	pthesis_node = NULL;
	*current_token = (*current_token)->next;
	pthesis_node = parse_tokens_to_ast(*current_token);
	while (*current_token && (*current_token)->op != CLOSE)
		*current_token = (*current_token)->next;
	if (*current_token && (*current_token)->op == CLOSE)
		*current_token = (*current_token)->next;
	return (pthesis_node);
}

t_ast	*integrate_ast_node(t_ast *root, t_ast *pthesis_node)
{
	t_ast	*current_node;

	if (root)
	{
		if (!root->left)
			root->left = pthesis_node;
		else if (!root->right)
			root->right = pthesis_node;
		else
		{
			current_node = root;
			while (current_node->right)
				current_node = current_node->right;
			current_node->right = pthesis_node;
		}
		return (root);
	}
	else
	{
		return (pthesis_node);
	}
}

t_ast	*handle_parentheses_ast(t_token **current_token, t_ast *root)
{
	t_ast	*pthesis_node;

	pthesis_node = parse_parentheses(current_token);
	return (integrate_ast_node(root, pthesis_node));
}
