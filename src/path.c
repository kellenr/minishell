/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 02:10:15 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/10 01:06:09 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to search for a command in the PATH.
 * Returns the full path to the command if found, otherwise NULL.
 */
char	*find_path(char *cmd, char **env)
{
	char	**path;
	int		i;

	i = 0;
	path = NULL;
	while (*env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			path = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	if (!path)
		return (NULL);
	return (get_path(cmd, path));
}

/*
 * Function to get the full path of a command.
 * Takes the command name and the paths as arguments.
 * Returns the full path of the command.
 */
char	*get_path(char *cmd, char **paths)
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
}

