/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 21:04:23 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/08 21:23:10 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to check if a string is a valid number.
 * Returns 1 if valid, 0 otherwise.
 */
int	is_number(const char *str)
{
	int i = 0;

	if (str[0] == '-' || str[0] == '+') // Handle optional sign
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return 0;
		i++;
	}
	return 1;
}

/*
 * Function to handle the exit command.
 * Takes an array of arguments (argv) and the number of arguments (argc).
 * If an argument is provided, it uses that as the exit status.
 * If no argument is provided, it exits with the status of the last executed command.
 */
void	ft_exit(t_cmd *cmd)
{
	int exit_status;

	if (cmd->argc > 1)
	{
		if (is_number(cmd->tokens[1]))
		{
			exit_status = ft_atoi(cmd->tokens[1]);
			exit(exit_status);
		}
		else
		{
			ft_printf("exit: %s: numeric argument required\n", cmd->tokens[1]);
			exit(255); // Common convention for invalid argument
		}
	}
	else
	{
		exit(g_status);
	}
}
