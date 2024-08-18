/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:48:37 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/18 02:03:27 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_env(t_cmd *cmd, char **envp)
{
	cmd->env = ft_calloc((array_len(envp) + 1), sizeof(char *));
	if (!cmd->env)
	{
		perror("Memory allocation error");
		return (1);
	}
	cmd->env_list = NULL;
	cmd->export_list = NULL;
	if (init_arr_and_list(cmd, envp) != 0)
	{
		free_array(cmd->env, array_len(envp));
		free_env_list(cmd->env_list);
		free_env_list(cmd->export_list);
		perror("Allocation error");
		return (1);
	}
	return (0);
}

// int	init_arr_and_list(t_cmd *cmd, char **envp)
// {
// 	int		i;
// 	t_env	*new_node;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		cmd->env[i] = ft_strdup(envp[i]);
// 		if (!cmd->env[i])
// 		{
// 			free_array(cmd->env, i + 1);
// 			free_env_list(cmd->export_list);
// 			return (-1);
// 		}
// 		new_node = create_env_node(envp[i]);
// 		if (!new_node)
// 		{
// 			free_array(cmd->env, i + 1);
// 			free_env_list(cmd->export_list);
// 			return (-1);
// 		}
// 		add_env_node(&cmd->export_list, new_node);
// 		i++;
// 	}
// 	cmd->env[i] = NULL;
// 	return (0);
// }

int	init_arr_and_list(t_cmd *cmd, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		cmd->env[i] = ft_strdup(envp[i]);
		if (!cmd->env[i])
		{
			free_array(cmd->env, i + 1);
			return (-1);
		}
		i++;
	}
	cmd->env[i] = NULL;
	if (init_env_and_export(cmd, envp) != 0)
	{
		free_array(cmd->env, i + 1);
		free_env_list(cmd->export_list);
		free_env_list(cmd->env_list);
	}
	return (0);
}

int	parse_env_str(const char *env_str, char **name, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(env_str, '=');
	if (!equal_sign)
		return (0);
	*name = ft_strndup(env_str, equal_sign - env_str);
	if (!*name)
		return (0);
	*value = ft_strdup(equal_sign + 1);
	if (!*value)
	{
		free(*name);
		return (0);
	}
	return (1);
}

void	add_env_node(t_env **env_list, t_env *node)
{
	t_env	*current;

	if (!*env_list)
		*env_list = node;
	else
	{
		current = *env_list;
		while (current->next)
			current = current->next;
		current->next = node;
	}
}

t_env	*create_env_node(const char *env_str)
{
	t_env	*new_node;
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	if (!parse_env_str(env_str, &name, &value))
	{
		free(new_node);
		return (NULL);
	}
	new_node->name = name;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}
