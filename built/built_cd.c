/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 21:17:54 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/09 00:29:14 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to get the target directory.
 * Takes a command structure and a pointer to the previous directory.
 * Returns the target directory or NULL if an error occurs.
 */
char	*get_dir(t_cmd *cmd, char *prev_dir)
{
	char	*home;

	if (cmd->argc < 2 || ft_strcmp(cmd->tokens[1], "~") == 0)
	{
		home = getenv("HOME");
		if (!home)
		{
			ft_printf("cd: HOME not set\n");
			return (NULL);
		}
		return (home);
	}
	else if (ft_strcmp(cmd->tokens[1], "-") == 0)
	{
		if (!prev_dir)
		{
			ft_printf("cd: OLDPWD not set\n");
			return (NULL);
		}
		ft_printf("%s\n", prev_dir);
		return (prev_dir);
	}
	else
		return (cmd->tokens[1]);
}

/*
 * Function to change the directory.
 * Takes a command structure as an argument.
 * Handles special cases for 'cd ~' and 'cd -'.
 */
int	ft_cd(t_cmd *cmd)
{
	static char	*prev_dir = NULL;
	char		cwd[1024];
	char		*target_dir;

	target_dir = get_dir(cmd, prev_dir);
	if (!target_dir)
		return (EXIT_FAILURE);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (EXIT_FAILURE);
	}
	if (chdir(target_dir) != 0)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	free(prev_dir);
	prev_dir = ft_strdup(cwd);
	return (EXIT_SUCCESS);
}

/* int	ft_cd(t_cmd *cmd)
{
	static char	*previous_dir = NULL;
	char		cwd[1024];
	char		*target_dir;

	if (cmd->argc < 2 || ft_strcmp(cmd->tokens[1], "~") == 0)
	{
		target_dir = getenv("HOME");
		if (!target_dir)
		{
			ft_printf("cd: HOME not set\n");
			return (EXIT_FAILURE);
		}
	}
	else if (ft_strcmp(cmd->tokens[1], "-") == 0)
	{
		if (!previous_dir)
		{
			ft_printf("cd: OLDPWD not set\n");
			return (EXIT_FAILURE);
		}
		target_dir = previous_dir;
		ft_printf("%s\n", previous_dir); // Print the previous directory
	}
	else
		target_dir = cmd->tokens[1];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (EXIT_FAILURE);
	}
	if (chdir(target_dir) != 0)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	free(previous_dir);
	previous_dir = ft_strdup(cwd);
	return (EXIT_SUCCESS);
} */
