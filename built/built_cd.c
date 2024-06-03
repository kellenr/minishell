/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 21:17:54 by keramos-          #+#    #+#             */
/*   Updated: 2024/05/28 18:30:47 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to change the current working directory.
 * If no argument is given, changes to the home directory.
 * If an argument is provided, changes to the specified directory.
 * Prints an error message if the directory change fails.
 * Returns EXIT_SUCCESS on success, EXIT_FAILURE on error.
*/
int	ft_cd(t_cmd *cmd)
{
	char	*home;

	if (cmd->argc < 2)
	{
		home = getenv("HOME");
		if (!home)
		{
			ft_printf("cd: HOME not set\n");
			return (EXIT_FAILURE);
		}
		if (chdir(home) != 0)
		{
			perror("cd");
			return (EXIT_FAILURE);
		}
	}
	else
	{
		if (chdir(cmd->tokens[1]) != 0)
		{
			perror("cd");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
