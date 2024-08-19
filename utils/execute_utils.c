/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:41:55 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/19 18:59:03 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command_helper(t_ast *root, t_msh *msh)
{
	t_cmd	*cmd;

	cmd = ast_to_cmd(root);
	if (!cmd)
	{
		ft_printf("Error: Failed to create command");
		msh->exit_status = 1;
		return ;
	}
	cmd->msh = msh;
	if (init_env(cmd, msh->env) != 0)
	{
		ft_printf("Error: Failed to initialize env");
		msh->exit_status = 1;
		free_cmd(cmd);
		return ;
	}
	if (is_builtin(cmd->cmd))
		cmd->msh->exit_status = execute_builtin(cmd);
	else
		execute_command(cmd);
	free_cmd(cmd);
}

void	fork_and_execute(t_cmd *cmd, char *cmd_path)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		execute_in_child(cmd_path, cmd->tokens, cmd->env);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		handle_child_status(cmd, status);
	}
	else
	{
		perror("fork");
		cmd->msh->exit_status = 1;
	}
}

char	*expand_command(t_cmd *cmd)
{
	char	*expanded_cmd;

	expanded_cmd = exp_env_var(cmd->tokens[0], cmd->msh);
	if (!expanded_cmd || ft_strlen(expanded_cmd) == 0)
	{
		prt_error("msh: command not found: %s\n", cmd->tokens[0]);
		cmd->msh->exit_status = 126;
		free(expanded_cmd);
		return (NULL);
	}
	return (expanded_cmd);
}

char	*handle_path_search(char *expanded_cmd, t_cmd *cmd, int *allocated)
{
	char	*cmd_path;

	cmd_path = find_path(expanded_cmd, cmd->env);
	if (cmd_path)
		*allocated = 1;
	else
	{
		prt_error("msh: %s: command not found\n", expanded_cmd);
		cmd->msh->exit_status = 127;
	}
	free(expanded_cmd);
	return (cmd_path);
}

char	*process_path_stat(char *expanded_cmd, struct stat *path_stat, \
		t_cmd *cmd, int *allocated)
{
	char	*result;

	if (S_ISDIR(path_stat->st_mode))
	{
		prt_error("msh: %s: Is a directory\n", expanded_cmd);
		cmd->msh->exit_status = 126;
	}
	else if (!(path_stat->st_mode & S_IXUSR))
	{
		prt_error("msh: %s: Permission denied\n", expanded_cmd);
		cmd->msh->exit_status = 126;
	}
	else
	{
		result = ft_strdup(expanded_cmd);
		if (result)
			*allocated = 1;
		free(expanded_cmd);
		return (result);
	}
	return (NULL);
}
