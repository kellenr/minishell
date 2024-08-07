/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 00:20:12 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/07 11:17:15 by fibarros         ###   ########.fr       */
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
	int	i;

	if (!root)
		return ;
	printf("Freeing node at %p\n", (void *)root);
	free_ast(root->left);
	free_ast(root->right);
	if (root->command)
	{
		printf("Freeing command at %p: %s\n", (void *)root->command, \
		root->command);
		free(root->command);
		root->command = NULL;
	}
	if (root->args)
	{
		i = 0;
		while (root->args[i])
		{
			printf("Freeing arg at %p: %s\n", (void *)root->args[i], \
			root->args[i]);
			free(root->args[i]);
			i++;
		}
		printf("Freeing args array at %p\n", (void *)root->args);
		free(root->args);
	}
	printf("Freeing root node at %p\n", (void *)root);
	free(root);
	root = NULL;
}

void	free_msh(t_msh *msh)
{
	int	i;

	i = 0;
	if (!msh)
		return ;
	if (msh->env)
		free_array(msh->env, array_len(msh->env));
	msh->env = NULL;
	free(msh);
}

void	free_redir(t_redir *redir)
{
	if (!redir)
		return ;
	if (redir->input_file)
		free(redir->input_file);
	if (redir->output_file)
		free(redir->output_file);
	if (redir->append_file)
		free(redir->append_file);
	if (redir->here_doc_delim)
		free(redir->here_doc_delim);
	free(redir);
}
