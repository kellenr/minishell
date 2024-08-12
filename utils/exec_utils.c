/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:57:47 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/12 16:22:21 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command_path(t_cmd *cmd)
{
	char	*cmd_path;

	cmd_path = find_path(cmd->tokens[0], cmd->env);
	if (!cmd_path)
	{
		ft_printf("msh: %s: command not found\n", cmd->tokens[0]);
		cmd->msh->exit_status = 127;
		return (NULL);
	}
	return (cmd_path);
}

void	execute_in_child(char *cmd_path, char **tokens, char **env)
{
	if (execve(cmd_path, tokens, env) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	handle_child_status(t_cmd *cmd, int status)
{
	if (WIFEXITED(status))
		cmd->msh->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			cmd->msh->exit_status = 131;
		else if (WTERMSIG(status) == SIGINT)
			cmd->msh->exit_status = 130;
		else
			cmd->msh->exit_status = 128 + WTERMSIG(status);
	}
	else
		cmd->msh->exit_status = 1;
}

int	check_tokens(t_cmd *cmd)
{
	if (!cmd->tokens)
	{
		perror("tokens not found");
		return (0);
	}
	return (1);
}

void	fork_and_execute(char *cmd_path, t_cmd *cmd, pid_t *pid, int *status)
{
	*pid = fork();
	if (*pid == 0)
		execute_in_child(cmd_path, cmd->tokens, cmd->env);
	else if (*pid > 0)
	{
		waitpid(*pid, status, 0);
		handle_child_status(cmd, *status);
	}
	else
	{
		perror("fork");
		cmd->msh->exit_status = 1;
	}
}
