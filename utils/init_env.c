/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:48:37 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/07 10:50:27 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	*init_env(t_cmd *cmd, char **envp)
// {
// 	cmd->env = ft_calloc((array_len(envp) + 1), sizeof(char *));
// 	if (!cmd->env)
// 	{
// 		perror("Memory allocation error");
// 		exit(EXIT_FAILURE);
// 	}
// 	cmd->env_list = NULL;
// 	if (init_arr_and_list(cmd, envp) != 0)
// 	{
// 		free_arr(cmd->env, array_len(envp));
// 		free_env_list(cmd->env_list);
// 		perror("Allocation error");
// 		exit(EXIT_FAILURE);
// 	}
// 	return (NULL);
// }

int	init_env(t_cmd *cmd, char **envp)
{
	cmd->env = ft_calloc((array_len(envp) + 1), sizeof(char *));
	if (!cmd->env)
	{
		perror("Memory allocation error");
		return (1);
	}
	cmd->env_list = NULL;
	if (init_arr_and_list(cmd, envp) != 0)
	{
		free_array(cmd->env, array_len(envp));
		free_env_list(cmd->env_list);
		perror("Allocation error");
		return (1);
	}
	return (0);
}

int	init_arr_and_list(t_cmd *cmd, char **envp)
{
	int		i;
	t_env	*new_node;

	i = 0;
	while (envp[i])
	{
		cmd->env[i] = ft_strdup(envp[i]);
		if (!cmd->env[i])
		{
			free_array(cmd->env, i + 1);
			free_env_list(cmd->env_list);
			return (-1);
		}
		new_node = create_env_node(envp[i]);
		if (!new_node)
		{
			free_array(cmd->env, i + 1);
			free_env_list(cmd->env_list);
			return (-1);
		}
		add_env_node(&cmd->env_list, new_node);
		i++;
	}
	cmd->env[i] = NULL;
	return (0);
}

t_env	*create_env_node(const char *env_str)
{
	t_env	*new_node;
	char	*equal_sign;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	equal_sign = ft_strchr(env_str, '=');
	if (!equal_sign)
	{
		free(new_node);
		return (NULL);
	}
	new_node->name = ft_strndup(env_str, equal_sign - env_str);
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = ft_strdup(equal_sign + 1);
	if (!new_node->value)
	{
		free(new_node->name);
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
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
