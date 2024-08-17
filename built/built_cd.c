/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 21:17:54 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/18 00:22:59 by keramos-         ###   ########.fr       */
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
		// home = getenv("HOME");
		home = ft_getenv("HOME", cmd);
		if (!home)
		{
			prt_error("cd: HOME not set\n", NULL);
			return (NULL);
		}
		return (home);
	}
	else if (ft_strcmp(cmd->tokens[1], "-") == 0)
	{
		if (!prev_dir)
		{
			prt_error("cd: OLDPWD not set\n", NULL);
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
	char		cwd[MAX_TKS];
	char		*target_dir;

	if (cmd->argc > 2)
	{
		prt_error("cd: too many arguments\n", NULL);
		return (EXIT_FAILURE);
	}
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

char	*ft_getenv(char *name, t_cmd *cmd)
{
	t_env	*env;
	size_t	name_len;

	name_len = ft_strlen(name);
	env = cmd->env_list;
	while (env != NULL)
	{
		if (ft_strncmp(env->name, name, name_len) == 0 && \
		env->name[name_len] == '\0')
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
