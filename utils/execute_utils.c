/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:41:55 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/12 14:51:52 by keramos-         ###   ########.fr       */
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
