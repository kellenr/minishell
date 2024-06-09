/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 02:10:15 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/09 22:19:31 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to search for a command in the PATH.
 * Returns the full path to the command if found, otherwise NULL.
 */
/* char	*find_path(char *cmd, char **env)
{
	char	**path;
	int		i;

	path = NULL;
	while (*env[i])
	{
		if (ft_strncmp("PATH=", env[i] 5) == 0)
		{
			paths = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	if (!path)
		return (NULL);
	return (get_path(cmd, path));
} */

/*
 * Function to get the full path of a command.
 * Takes the command name and the paths as arguments.
 * Returns the full path of the command.
 */
/* char	*get_path(char *cmd, char **paths)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
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

