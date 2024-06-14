/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 23:14:16 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/14 13:43:48 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char *op_to_string(t_op op)
{
	switch (op) {
		case NONE: return "NONE";
		case PIPE: return "PIPE";
		case REDIR_APPEND: return "REDIR_APPEND";
		case REDIR_REPLACE: return "REDIR_REPLACE";
		case REDIR_HERE_DOC: return "REDIR_HERE_DOC";
		case REDIR_INPUT: return "REDIR_INPUT";
		case AND: return "AND";
		case OR: return "OR";
		default: return "UNKNOWN";
	}
}

void print_ast(t_ast *root, int level, char *branch)
{
	if (!root) return;

	for (int i = 0; i < level; i++) printf("  ");
	printf("%s─%s (%s)\n", branch, root->value, op_to_string(root->op));
	// Indicate presence of left and right children
	if (root->left || root->right)
	{
		printf(" [L: %s, R: %s] \n", \
		root->left ? root->left->value : "NULL",\
		root->right ? root->right->value : "NULL");
	}

	// Print left child
	if (root->left) {
		print_ast(root->left, level + 1, "L");
	}

	// Print right child
	if (root->right) {
		print_ast(root->right, level + 1, "R");
	}
}
