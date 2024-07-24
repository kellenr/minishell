/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:48:37 by fibarros          #+#    #+#             */
/*   Updated: 2024/07/22 13:53:37 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*init_env(t_cmd *cmd, char **envp)
{
	cmd->env = ft_calloc((array_len(envp) + 1), sizeof(char *));
	if (!cmd->env)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	cmd->env_list = NULL;
	if (init_arr_and_list(cmd, envp) != 0)
	{
		free_env(cmd);
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}
	return (NULL);
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
			return (-1);
		new_node = create_env_node(envp[i]);
		if (!new_node)
			return (-1);
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
	new_node->value = ft_strdup(equal_sign + 1);
	new_node->next = NULL;
	if (!new_node->name || !new_node->value)
	{
		free(new_node->name);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
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
