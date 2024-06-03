/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 00:20:12 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/02 19:00:42 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to free the memory allocated for a command structure.
 * Frees each argument string and the tokens array, then frees the command
 * structure itself.
 */
void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->tokens)
	{
		i = 0;
		while (cmd->tokens[i])
		{
			free(cmd->tokens[i]);
			i++;
		}
		free(cmd->tokens);
	}
	if (cmd->env)
	{
		i = 0;
		while (cmd->env[i])
		{
			free(cmd->env[i]);
			i++;
		}
		free(cmd->env);
	}
	free(cmd);
}

/*
 * Function to free the list of tokens.
 * Takes the head of the token list as an argument.
 */
void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);
		free(temp);
	}
}

/*
 * Function to free the AST.
 * Takes the root of the AST as an argument.
 */
void	free_ast(t_ast *root)
{
	if (!root)
		return ;
	free_ast(root->left);
	free_ast(root->right);
	free(root->value);
	free(root);
}
