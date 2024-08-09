/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_and_or_parent.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:17:06 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/09 16:23:14 by fibarros         ###   ########.fr       */
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

t_ast	*handle_parentheses_ast(t_token **current_token, t_ast *root)
{
	t_ast	*parentheses_node;

	parentheses_node = malloc(sizeof(t_ast));
	if (!parentheses_node)
		ft_error("malloc failed");
	parentheses_node->op = SUBSHELL;
	parentheses_node->left = NULL;
	parentheses_node->right = NULL;
	parentheses_node->command = NULL;
	parentheses_node->args = NULL;
	parentheses_node->redir = NULL;
	(*current_token) = (*current_token)->next;
	parentheses_node->left = parse_tokens_to_ast(*current_token);
	if (!parentheses_node->left)
	{
		free(parentheses_node);
		return (NULL);
	}
	while (*current_token && (*current_token)->op != CLOSE)
		(*current_token) = (*current_token)->next;
	if (*current_token)
		(*current_token) = (*current_token)->next;
	if (root)
		root->right = parentheses_node;
	return (parentheses_node);
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
