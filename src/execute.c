/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:54:08 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/18 00:47:13 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to count the number of nodes in the AST.
 * Takes the root of the AST as an argument.
 * Returns the number of nodes.
 */
int	count_ast_nodes(t_ast *root)
{
	if (!root)
		return (0);
	return (1 + count_ast_nodes(root->left) + count_ast_nodes(root->right));
}

/*
 * Function to populate the tokens array from an AST.
 * Takes the root of the AST and the tokens array as arguments.
 * Returns the number of tokens.
 */
void	populate_tokens_array(t_ast *root, char **tokens, int *index)
{
	if (!root)
		return ;
	tokens[*index] = ft_strdup(root->command);
	(*index)++;
	if (root->left)
		populate_tokens_array(root->left, tokens, index);
	if (root->right)
		populate_tokens_array(root->right, tokens, index);
}

/*
 * Function to execute commands represented by the AST.
 * Takes the root of the AST as an argument.
 *
 * EDIT: added the new initialization of the environment in the command struct
 */
void	execute_ast(t_ast *root, t_msh *msh)
{
	if (!root)
		return ;
	if (root->op == PIPE)
		execute_pipes(root, msh);
	else if (root->op == REDIR_APPEND || root->op == REDIR_REPLACE || \
			root->op == REDIR_HERE_DOC || root->op == REDIR_INPUT)
		handle_redirection(root, msh);
	else if (root->op == AND || root->op == OR)
		handle_logical_op(root, msh);
	else if (root->op == SUBSHELL)
		handle_parentheses_op(root, msh);
	else
		execute_command_helper(root, msh);
}

/*
 * Function to execute built-in commands.
 * Takes a command structure as an argument.
 * Executes the built-in command if recognized.
 */
int	execute_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd, "exit") == 0)
		ft_exit(cmd);
	else if (ft_strcmp(cmd->cmd, "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		return (ft_echo(cmd));
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		return (ft_cd(cmd));
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		return (ft_env(cmd));
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		return (ft_export(cmd));
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		return (ft_unset(cmd));
	return (-1);
}

/*
 * Function to execute a command.
 * Takes a command structure as an argument.
 * Forks a child process to execute the command and waits for it to complete.
 * Updates the global status variable with the exit status of the command.
 */
void	execute_command(t_cmd *cmd)
{
	char	*cmd_path;
	int		cmd_flag;

	cmd_flag = 0;
	if (!check_tokens(cmd))
		return ;
	cmd_path = get_command_path(cmd, &cmd_flag);
	if (!cmd_path)
	{
		return ;
	}
	handle_non_interactive();
	fork_and_execute(cmd, cmd_path);
	if (cmd_flag == 1 )
		free(cmd_path);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
