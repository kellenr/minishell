/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:30:43 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/05 16:42:17 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_env(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->env[i])
	{
		free(cmd->env[i]);
		i++;
	}
	free(cmd->env);
	free_env_list(cmd->env_list);
}

void	free_env_list(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		free(current->name);
		free(current->value);
		free(current);
	}
}

void	print_env_list(t_env *env_list)
{
	while (env_list)
	{
		printf("%s=%s\n", env_list->name, env_list->value);
		env_list = env_list->next;
	}
}
