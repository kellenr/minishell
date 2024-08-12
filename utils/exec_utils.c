/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:57:47 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/12 20:07:10 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command_path(t_cmd *cmd)
{
	char		*cmd_path;
	struct stat	path_stat;
	char		*expanded_cmd;

	expanded_cmd = exp_env_var(cmd->tokens[0], cmd->msh);
	if (lstat(expanded_cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_printf("msh: %s: Is a directory\n", expanded_cmd);
		cmd->msh->exit_status = 126;
		free(expanded_cmd);
		return (NULL);
	}
	cmd_path = find_path(cmd->tokens[0], cmd->env);
	if (!cmd_path)
	{
		ft_printf("msh: %s: command not found\n", cmd->tokens[0]);
		cmd->msh->exit_status = 127;
		free(expanded_cmd);
		return (NULL);
	}
	free(expanded_cmd);
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
