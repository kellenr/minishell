/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:27:05 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/15 16:19:21 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_token(char *token, char *error_message)
{
	if (!token)
		return (0);
	if ((token[0] == '=') || ft_isdigit(token[0]) || \
			ft_strchr(token, '\'') || ft_strchr(token, '"') || \
			ft_strchr(token, '-'))
	{
		ft_strcpy(error_message, "export `");
		ft_strcat(error_message, token);
		ft_strcat(error_message, "': not a valid identifier");
		return (0);
	}
	else
		return (1);
}

int	is_valid_export(char *token)
{
	char	error_message[100];

	ft_bzero(error_message, sizeof(error_message));
	if (!check_valid_token(token, error_message))
	{
		ft_printf("%s\n", error_message);
		return (0);
	}
	return (1);
}

int	init_env_and_export(t_cmd *cmd, char **envp)
{
	int		i;
	t_env	*export_node;
	t_env	*env_node;

	i = 0;
	while (envp[i])
	{
		export_node = create_env_node(envp[i]);
		if (!export_node)
		{
			free_env_list(cmd->export_list);
			free_env_list(cmd->env_list);
			return (-1);
		}
		add_env_node(&cmd->export_list, export_node);
		env_node = create_env_node(envp[i]);
		if (!env_node)
		{
			free_env_list(cmd->export_list);
			free_env_list(cmd->env_list);
			return (-1);
		}
		add_env_node(&cmd->env_list, env_node);
		i++;
	}
	// print_env_list(cmd->env_list);
	return (0);
}

