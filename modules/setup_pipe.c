/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:35:09 by keramos-          #+#    #+#             */
/*   Updated: 2024/07/01 00:33:13 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to execute a pipe command.
 */
void	execute_pipes(t_ast *root, t_msh *msh)
{
	int		pipefd[2];
	pid_t	p1;
	pid_t	p2;

	if (root->op != PIPE)
	{
		execute_ast(root, msh);
		return;
	}
	if (pipe(pipefd) == -1)
		ft_error("pipe");
	p1 = fork_first_child(root, msh, pipefd);
	p2 = fork_second_child(root, msh, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(p1, NULL, 0);
	waitpid(p2, NULL, 0);
	return ;
}

/*
 * Function to fork the first child process.
 */
pid_t	fork_first_child(t_ast *root, t_msh *msh, int pipefd[2])
{
	pid_t	p1;

	p1 = fork();
	if (p1 == -1)
		ft_error("fork p1");
	if (p1 == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_ast(root->left, msh);
		exit(msh->exit_status);
	}
	return (p1);
}

/*
 * Function to fork the second child process.
 */
pid_t	fork_second_child(t_ast *root, t_msh *msh, int pipefd[2])
{
	pid_t	p2;

	p2 = fork();
	if (p2 == -1)
		ft_error("fork p2");
	if (p2 == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_ast(root->right, msh);
		exit(msh->exit_status);
	}
	return (p2);
}

// int count_commands(t_ast *root)
// {
// 	if (root == NULL)
//         return 0;

//     if (root->op == PIPE) {
//         int left_count = count_commands(root->left);
//         int right_count = count_commands(root->right);
//         printf("PIPE node: left_count = %d, right_count = %d\n", left_count, right_count);
//         return left_count + right_count;
//     } else {
//         printf("Command node: %s\n", root->value); // Assuming root->cmd is a string
//         return 1;
//     }
// }
