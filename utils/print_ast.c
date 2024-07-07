/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 23:14:16 by keramos-          #+#    #+#             */
/*   Updated: 2024/07/07 15:25:34 by keramos-         ###   ########.fr       */
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

/* void print_ast(t_ast *root, int level, char *branch)
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
} */

void print_ast_helper(t_ast *node, int level)
{
	if (node == NULL) return;
	for (int i = 0; i < level; i++) printf("  ");

	if (node->op == PIPE) {
		printf("|- PIPE\n");
	}else if (node->op == REDIR_INPUT) {
		printf("|- <\n");
	} else if (node->op == REDIR_REPLACE) {
		printf("|- >\n");
	} else {
		printf("|- Command: %s\n", node->command);
		for (int i = 0; node->args && node->args[i] != NULL; i++) {
			for (int j = 0; j < level + 1; j++) printf("  ");
			printf("|- Arg: %s\n", node->args[i]);
		}
	}

	if (node->left != NULL) {
		for (int i = 0; i < level; i++) printf("  ");
		printf("|- Left:\n");
		print_ast_helper(node->left, level + 1);
		if (node->redir) {
			if (node->redir->input_file != NULL) {
				for (int i = 0; i < level + 1; i++) printf("  ");
				printf("|- Input File: %s\n", node->redir->input_file);
			}
			if (node->redir->output_file != NULL) {
				for (int i = 0; i < level + 1; i++) printf("  ");
				printf("|- Output File: %s\n", node->redir->output_file);
			}
		}
	}
	if (node->right != NULL) {
		for (int i = 0; i < level; i++) printf("  ");
		printf("|- Right:\n");
		print_ast_helper(node->right, level + 1);
		if (node->redir) {
			if (node->redir->input_file != NULL) {
				for (int i = 0; i < level + 1; i++) printf("  ");
				printf("|- Input File: %s\n", node->redir->input_file);
			}
			if (node->redir->output_file != NULL) {
				for (int i = 0; i < level + 1; i++) printf("  ");
				printf("|- Output File: %s\n", node->redir->output_file);
			}
		}
	}
}

void print_ast(t_ast *node)
{
	printf("AST:\n");
	print_ast_helper(node, 0);
}
