/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 02:52:41 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/09 02:52:46 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to check if a value is a valid operator.
 * Takes the token value as an argument.
 * Returns the corresponding operator enum.
 */
t_op	valid_op(const char *operator)
{
	if (!operator)
		return (NONE);
	if (cmp_s(operator, "|") == 0)
		return (PIPE);
	if (cmp_s(operator, ">>") == 0)
		return (REDIR_APPEND);
	if (cmp_s(operator, ">") == 0)
		return (REDIR_REPLACE);
	if (cmp_s(operator, "<<") == 0)
		return (REDIR_HERE_DOC);
	if (cmp_s(operator, "<") == 0)
		return (REDIR_INPUT);
	if (cmp_s(operator, "&&") == 0)
		return (AND);
	if (cmp_s(operator, "||") == 0)
		return (OR);
	if (cmp_s(operator, "$") == 0)
		return (DOLLAR);
	return (NONE);
}

/*
 * Function to check if a command is a built-in command.
 * Takes the command name as an argument.
 * Returns 1 if the command is a built-in, 0 otherwise.
 */
int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	return (0);
}
