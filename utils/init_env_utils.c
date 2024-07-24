/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:30:43 by fibarros          #+#    #+#             */
/*   Updated: 2024/07/22 13:54:11 by keramos-         ###   ########.fr       */
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
		// current = current->next;
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
