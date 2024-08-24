/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 02:10:15 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/23 10:30:22 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to search for a command in the PATH.
 * Returns the full path to the command if found, otherwise NULL.
 */
char	*find_path(char *cmd, char **env, int *flag)
{
	char	**path;
	int		i;
	char	*full_path;

	i = 0;
	path = NULL;
	if (find_path_var(env) == 0)
		return (NULL);
	while (*env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			path = ft_split(env[i] + 5, ':');
			if (!path)
				return (NULL);
			break ;
		}
		i++;
	}
	if (!path)
		return (NULL);
	full_path = get_path(cmd, path, flag);
	free_array(path, array_len(path));
	return (full_path);
}

/*
 * Function to get the full path of a command.
 * Takes the command name and the paths as arguments.
 * Returns the full path of the command.
 */
char	*get_path(char *cmd, char **paths, int *flag)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	if (check_access(cmd, flag))
		return (cmd);
	*flag = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

int	find_path_var(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_access(char *cmd, int *flag)
{
	if (access(cmd, X_OK) == 0)
	{
		*flag = 1;
		return (1);
	}
	return (0);
}
