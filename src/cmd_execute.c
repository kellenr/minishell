/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:54:08 by keramos-          #+#    #+#             */
/*   Updated: 2024/07/07 15:27:58 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to process a command prompt string.
 * Takes the prompt string as an argument.
 */
void	process_cmd(char *prompt, t_msh *msh)
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
	token_var_exp(tokens, msh);
	free(preprocessed_input);
	if (!tokens)
	{
		ft_printf("Error: Unmatched quote detected\n");
		msh->exit_status = 1;
		return ;
	}
	cmd_tree = parse_tokens_to_ast(tokens);
	print_ast(cmd_tree);
	execute_ast(cmd_tree, msh);
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
	int		i;

	i = 0;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	count = 0;
	while (root->args[count] != NULL)
		count++;
	cmd->tokens = (char **)malloc(sizeof(char *) * (count + 1));
	if (!cmd->tokens)
	{
		free(cmd);
		return (NULL);
	}
	while (i < count)
	{
		cmd->tokens[i] = ft_strdup(root->args[i]);
		i++;
	}
	cmd->tokens[count] = NULL;
	cmd->cmd = ft_strdup(root->command);
	cmd->env = NULL;
	cmd->argc = count;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}
