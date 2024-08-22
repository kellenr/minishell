/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:57:47 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/19 18:57:47 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command_path(t_cmd *cmd, int *allocated)
{
	char		*expanded_cmd;
	char		*result;
	struct stat	path_stat;

	*allocated = 0;
	expanded_cmd = expand_command(cmd);
	if (!expanded_cmd)
		return (NULL);
	if (!ft_strchr(expanded_cmd, '/'))
		return (handle_path_search(expanded_cmd, cmd, allocated));
	if (lstat(expanded_cmd, &path_stat) == 0)
	{
		result = process_path_stat(expanded_cmd, &path_stat, cmd, allocated);
		return (result);
	}
	else
	{
		prt_error("msh: %s: No such file or directory\n", expanded_cmd);
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
