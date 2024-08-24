/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:21:51 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/16 14:47:10 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_cmd *cmd)
{
	int		i;

	if (cmd->argc == 1)
		return (0);
	i = 1;
	while (i < cmd->argc)
	{
		if (is_valid_unset(cmd->tokens[i]))
			remove_env_var(&(cmd->env_list), cmd->tokens[i]);
		i++;
	}
	if (update_env_msh(cmd->msh, cmd->env_list) != 0)
	{
		ft_printf("error updating msg env\n");
		return (1);
	}
	return (0);
}

int	is_valid_unset(char *token)
{
	char	error_message[100];

	ft_bzero(error_message, sizeof(error_message));
	if (!check_valid_unset_token(token, error_message))
	{
		ft_error(error_message);
		return (0);
	}
	return (1);
}

int	check_valid_unset_token(char *token, char *error_message)
{
	if (!token)
		return (1);
	if ((ft_strchr(token, '=')) || (ft_isdigit(token[0])) || \
			(ft_strchr(token, '\'')) || (ft_strchr(token, '"')) || \
			(ft_strchr(token, '$')) || (token[0] == '/'))
	{
		ft_strcpy(error_message, "unset `");
		ft_strcat(error_message, token);
		ft_strcat(error_message, "': not a valid identifier");
		return (0);
	}
	else
		return (1);
}

void	remove_env_var(t_env **env_list, char *name)
{
	t_env	*current;
	t_env	*prev;

	current = *env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
