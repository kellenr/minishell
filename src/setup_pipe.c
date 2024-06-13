/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:35:09 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/09 20:06:28 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to set up the pipe between two commands.
 * Takes the command structure and the pipe file descriptor as arguments.
 */
void	setup_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
	{
		ft_error("pipe");
	}
}

/*
 * Function to close the pipe file descriptors.
 * Takes the pipe file descriptor as an argument.
 */
void	close_pipe(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

/*
 * Function to execute the command on the right side of the pipe.
 * Takes the command structure and the pipe file descriptor as arguments.
 */
void	execute_right_pipe(t_cmd *cmd, int *pipe_fd)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	execute_command(cmd);
}

/*
 * Function to execute the command on the left side of the pipe.
 * Takes the command structure and the pipe file descriptor as arguments.
 */
void	execute_left_pipe(t_cmd *cmd, int *pipe_fd)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	execute_command(cmd);
}

/*
 * Function to execute the command on both sides of the pipe.
 * Takes the command structure and the pipe file descriptor as arguments.
 */
void	execute_pipe(t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	int		pipe_fd[2];

	pid = fork();
	if (pid == -1)
	{
		ft_error("fork");
	}
	if (pid == 0)
	{
		execute_right_pipe(cmd->next, pipe_fd);
	}
	else
	{
		execute_left_pipe(cmd, pipe_fd);
		waitpid(pid, &status, 0);
		close_pipe(pipe_fd);
	}
}



