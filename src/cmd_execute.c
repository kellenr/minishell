/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:54:08 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/18 04:02:03 by keramos-         ###   ########.fr       */
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

	if (!prompt || !*prompt)
		return ;
	trimmed_prompt = trim_whitespace(prompt);
	if (!*trimmed_prompt || !trimmed_prompt)
	{
		free(trimmed_prompt);
		return ;
	}
	preprocessed_input = process_input(trimmed_prompt);
	free(trimmed_prompt);
	if (!preprocessed_input)
		ft_error("Error: failed to process input");
	tokens = tokenize(preprocessed_input, msh);
	free(preprocessed_input);
	if (!tokens)
		return ;
	if (tokens->broken)
	{
		prt_error("Error: Unmatched quote detected\n", NULL);
		msh->exit_status = 1;
		free_tokens(tokens);
		return ;
	}
	parse_and_execute(tokens, msh);
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

	count = 0;
	cmd = init_cmd();
	if (!cmd)
		return (NULL);
	cmd->tokens = copy_tokens(root->args, &count);
	if (!cmd->tokens)
	{
		free(cmd);
		return (NULL);
	}
	cmd->cmd = ft_strdup(root->command);
	if (!cmd->cmd)
	{
		free_array(cmd->tokens, count);
		free_cmd(cmd);
		return (NULL);
	}
	cmd->argc = count;
	return (cmd);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->env = NULL;
	cmd->env_list = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

char	**copy_tokens(char **args, int *count)
{
	char	**tokens;
	int		i;

	i = 0;
	while (args[*count] != NULL)
		(*count)++;
	tokens = (char **)malloc(sizeof(char *) * (*count + 1));
	if (!tokens)
		return (NULL);
	while (i < *count)
	{
		tokens[i] = ft_strdup(args[i]);
		if (!tokens[i])
		{
			while (i > 0)
				free(tokens[i--]);
			free(tokens);
			return (NULL);
		}
		i++;
	}
	tokens[*count] = NULL;
	return (tokens);
}

void	parse_and_execute(t_token *tokens, t_msh *msh)
{
	t_ast	*cmd_tree;

	if (!tokens)
		return ;
	cmd_tree = parse_tokens_to_ast(tokens, msh);
	free_tokens(tokens);
	if (cmd_tree)
	{
		execute_ast(cmd_tree, msh);
		free_ast(cmd_tree);
	}
}
