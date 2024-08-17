/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filipa <filipa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:57:47 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/17 19:42:14 by filipa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command_path(t_cmd *cmd, int *allocated)
{
	char		*cmd_path;
	struct stat	path_stat;
	char		*expanded_cmd;
	char		*result;

	*allocated = 0;
	expanded_cmd = exp_env_var(cmd->tokens[0], cmd->msh);
	if (!expanded_cmd || ft_strlen(expanded_cmd) == 0)
	{
		cmd->msh->exit_status = 127;
		ft_printf("msh: command not found: %s\n", cmd->tokens[0]);
		free(expanded_cmd);
		return (NULL);
	}
	if (!ft_strchr(expanded_cmd, '/'))
	{
		cmd_path = find_path(expanded_cmd, cmd->env);
		if (cmd_path)
			*allocated = 1;
		else
		{
			ft_printf("msh: %s: command not found\n", expanded_cmd);
			cmd->msh->exit_status = 127;
		}
		free(expanded_cmd);
		return (cmd_path);
	}
	if (lstat(expanded_cmd, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_printf("msh: %s: Is a directory\n", expanded_cmd);
			cmd->msh->exit_status = 126;
		}
		else if (!(path_stat.st_mode & S_IXUSR))
		{
			ft_printf("msh: %s: Permission denied\n", expanded_cmd);
			cmd->msh->exit_status = 126;
		}
		else
		{
			result = ft_strdup(expanded_cmd);
			*allocated = 1;
			free(expanded_cmd);
			return (result);
		}
	}
	else
	{
		ft_printf("msh: %s: No such file or directory\n", expanded_cmd);
		cmd->msh->exit_status = 127;
	}
	free(expanded_cmd);
	return (NULL);
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
