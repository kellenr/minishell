/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:54:08 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/02 19:04:34 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to process a command prompt string.
 * Takes the prompt string as an argument.
 */
void	process_cmd(char *prompt)
{
	char	*trimmed_prompt;
	char	*preprocessed_input;
	t_token	*tokens;
	t_ast	*cmd_tree;

	if (!prompt || !*prompt)
		return ;
	trimmed_prompt = trim_whitespace(prompt);
	if (!*trimmed_prompt)
	{
		free(trimmed_prompt);
		return ;
	}
	preprocessed_input = process_input(trimmed_prompt);
	free(trimmed_prompt);
	tokens = tokenize(preprocessed_input);
	free(preprocessed_input);
	cmd_tree = parse_tokens_to_ast(tokens);
	execute_ast(cmd_tree);
	//free_tokens(tokens);
	//free_ast(cmd_tree);
}

/*
 * Function to create a command structure from an AST node.
 * Takes the AST node as an argument.
 * Returns a pointer to the created command structure.
 */
t_cmd	*ast_to_cmd(t_ast *root)
{
	t_cmd	*cmd;
	int		count;
	int		index;

	index = 0;
	count = count_ast_nodes(root);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->tokens = (char **)malloc(sizeof(char *) * (count + 1));
	if (!cmd->tokens)
	{
		free(cmd);
		return NULL;
	}
	populate_tokens_array(root, cmd->tokens, &index);
	cmd->tokens[count] = NULL; // Null-terminate the tokens array
	cmd->cmd = ft_strdup(root->value);
	cmd->env = NULL;
	cmd->argc = count;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}
