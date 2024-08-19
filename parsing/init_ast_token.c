/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ast_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:30:15 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/19 17:39:14 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to initialize a redirection structure.
 * Returns a pointer to the newly initialized redirection structure.
 */
t_redir	*init_redir(void)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
	{
		perror("init_redir: malloc failed");
		return (NULL);
	}
	redir->input_file = NULL;
	redir->output_file = NULL;
	redir->append_file = NULL;
	redir->here_doc_delim = NULL;
	return (redir);
}

/*
 * Function to initialize an AST node.
 * Returns a pointer to the newly initialized AST node.
 */
t_ast	*init_ast(t_token **current_token)
{
	t_ast	*node;

	node = create_ast_node();
	if (!node)
		return (NULL);
	if (*current_token && (*current_token)->op == NONE)
	{
		if (set_command_and_args(node, *current_token) == -1)
			return (NULL);
	}
	if (*current_token)
		(*current_token) = (*current_token)->next;
	return (node);
}

/*
 * Function to create a new AST node.
 * Returns a pointer to the newly created AST node.
 */
t_ast	*create_ast_node(void)
{
	t_ast	*node;

	node = init_ast_node();
	if (!node)
	{
		perror("malloc fail");
		return (NULL);
	}
	node->command = NULL;
	node->args = NULL;
	return (node);
}

/*
 * Function to create a new token.
 * Takes the token value as an argument.
 * Returns a pointer to the new token.
 */
t_token	*create_token(char *value, bool quoted_flag)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (quoted_flag)
		token->op = NONE;
	else
		token->op = valid_op(value);
	token->next = NULL;
	token->broken = false;
	return (token);
}

/*
 * Function to add a token to the end of the token list.
 * Takes a pointer to the head of the list and the token value as arguments.
 */
void	add_token(t_token **head, char *value, bool quoted_flag)
{
	t_token	*new;
	t_token	*temp;

	new = create_token(value, quoted_flag);
	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}
