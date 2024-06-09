/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:54:08 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/10 00:41:03 by keramos-         ###   ########.fr       */
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
	tokens[*index] = ft_strdup(root->value);
	(*index)++;
	if (root->left)
		populate_tokens_array(root->left, tokens, index);
	if (root->right)
		populate_tokens_array(root->right, tokens, index);
}

/*
 * Function to execute commands represented by the AST.
 * Takes the root of the AST as an argument.
 */
void	execute_ast(t_ast *root, t_msh *msh)
{
	t_cmd	*cmd;

	if (!root)
		return ;
	cmd = ast_to_cmd(root);
	cmd->env = msh->env;
	cmd->msh = msh;
	if (is_builtin(cmd->cmd))
	{
		execute_builtin(cmd);
	}
	else
	{
		execute_command(cmd);
	}
	free_cmd(cmd);
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
		ft_pwd();
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		ft_cd(cmd);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		ft_env(cmd);
	return (0);
}

/*
 * Function to execute a command.
 * Takes a command structure as an argument.
 * Forks a child process to execute the command and waits for it to complete.
 * Updates the global status variable with the exit status of the command.
 */
void	execute_command(t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	if (!cmd->tokens)
	{
		perror("tokend not found");
		return ;
	}
	cmd_path = search_path(cmd->tokens[0]);
	if (!cmd_path)
	{
		ft_printf("msh: %s: command not found\n", cmd->tokens[0]);
		cmd->msh->exit_status = 127;
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, cmd->tokens, cmd->env) == -1)
			perror("execve");
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (status >= 0)
			cmd->msh->exit_status = status;
		else
			cmd->msh->exit_status = 1;
	}
	else
	{
		perror("fork");
		cmd->msh->exit_status = 1;
	}
}
