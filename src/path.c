/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 02:10:15 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/09 03:00:24 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to find the path of a command.
 * Takes the command name and the environment as arguments.
 * Returns the path of the command.
 */
/* char	*find_path(char *cmd, char **env)
{
	char	*path;
	char	**paths;
	int		i;

	path = NULL;
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			paths = ft_split(*env + 5, ':');
			i = 0;
			while (paths[i])
			{
				path = ft_strjoin(paths[i], "/");
				path = ft_strjoin(path, cmd);
				if (access(path, F_OK) == 0)
				{
					free_split(paths);
					return (path);
				}
				free(path);
				i++;
			}
			free_split(paths);
		}
		env++;
	}
	return (NULL);
} */

/*
 * Function to search for a command in the PATH.
 * Returns the full path to the command if found, otherwise NULL.
 */
char	*search_path(const char *cmd)
{
	char *path_env = getenv("PATH");
	char *path = NULL;
	char *dir = NULL;
	size_t len;

	if (!path_env)
		return (NULL);
	path_env = strdup(path_env);
	if (!path_env)
		return NULL;
	dir = ft_strtoke(path_env, ":");
	while (dir)
	{
		len = ft_strlen(dir) + ft_strlen(cmd) + 2;
		path = malloc(len);
		if (!path)
		{
			free(path_env);
			return NULL;
		}
		snprintf(path, len, "%s/%s", dir, cmd);
		if (access(path, X_OK) == 0)
		{
			free(path_env);
			return path;
		}
		free(path);
		path = NULL;
		dir = ft_strtoke(NULL, ":");
	}
	free(path_env);
	return NULL;
}

