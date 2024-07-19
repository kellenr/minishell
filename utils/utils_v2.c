/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_v2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:12:05 by fibarros          #+#    #+#             */
/*   Updated: 2024/07/17 14:00:33 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_env_msh(t_msh *msh, t_env *env_list)
{
	int		len;
	int		len_current;
	char	**env_array;

	env_array = list_to_array(env_list);
	if (!env_array)
	{
		perror("failed to convert env list to array");
		return (-1);
	}
	len = array_len(env_array);
	len_current = array_len(msh->env);
	free_array(msh->env, len_current);
	msh->env = env_array;
	return (0);
}

char	**list_to_array(t_env *env_list)
{
	int		list_size;
	char	**env_array;
	t_env	*current;
	int		i;

	i = 0;
	list_size = 0;
	current = env_list;
	while (current)
	{
		list_size++;
		current = current->next;
	}
	env_array = malloc((list_size + 1) * sizeof(char *));
	if (!env_array)
	{
		perror("Memory allocation error");
		return (NULL);
	}
	env_array = populate_env_array(env_list, env_array, list_size);
	return (env_array);
}

char	**populate_env_array(t_env *env_list, char **env_array, int list_size)
{
	t_env	*current;
	int		i;
	size_t	len;

	current = env_list;
	i = 0;
	while (i < list_size)
	{
		len = ft_strlen(current->name) + ft_strlen(current->value) + 2;
		env_array[i] = malloc(len * sizeof(char *));
		if (!env_array[i])
		{
			free_array(env_array, i);
			return (NULL);
		}
		ft_strcpy(env_array[i], current->name);
		ft_strcat(env_array[i], "=");
		ft_strcat(env_array[i], current->value);
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	free_array(char **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	open_tmp_file(void)
{
	int	fd;

	fd = open("tmp_file", O_RDWR | O_TRUNC | O_APPEND | O_CREAT, 0777);
	if (fd == -1)
		ft_error("Failed to open temp file");
	return (fd);
}
