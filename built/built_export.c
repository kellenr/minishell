/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:57:00 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/19 12:07:18 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Export function that handles exporting environment variables.
 * If no arguments are provided (`cmd->argc == 1`), prints all environment
 * variables.
 * Otherwise, iterates through each argument to update or add environment
 * variables.
 * Updates both the command's environment list (`cmd->env_list`) and the
 * shell's environment (`cmd->msh->env`).
 * Returns 0 on success, -1 on error.
 */
int	ft_export(t_cmd *cmd)
{
	t_env	*export_list;
	int		i;

	export_list = cmd->export_list;
	if (cmd->argc == 1)
	{
		print_export(export_list);
		return (0);
	}
	i = 1;
	while (i < cmd->argc)
	{
		if (is_valid_export(cmd->tokens[i]))
			handle_export_vars(cmd, cmd->tokens[i]);
		else
			return (1);
		i++;
	}
	if (update_env_msh(cmd->msh, cmd->export_list) != 0)
	{
		perror("Error updating msh env");
		return (1);
	}
	return (0);
}

void	handle_export_vars(t_cmd *cmd, char *arg)
{
	char	*name;
	char	*equal_sign;
	char	*value;
	t_env	*existing_var;

	equal_sign = strchr(arg, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		name = ft_strdup(arg);
		value = ft_strdup(equal_sign + 1);
		handle_var_assignment(cmd, name, value);
	}
	else
	{
		name = ft_strdup(arg);
		existing_var = find_env_var(cmd->export_list, name);
		if (!existing_var)
			add_env_var(&cmd->export_list, name, ft_strdup(""));
	}
}

void	add_or_update_env_list(t_env **env_list, char *name, char *value)
{
	t_env	*existing_var;

	existing_var = find_env_var(*env_list, name);
	if (existing_var)
	{
		free(existing_var->value);
		existing_var->value = ft_strdup(value);
		free(name);
	}
	else
		add_env_var(env_list, ft_strdup(name), ft_strdup(value));
}

void	handle_var_assignment(t_cmd *cmd, char *name, char *value)
{
	t_env	*existing_var;

	existing_var = find_env_var(cmd->export_list, name);
	if (existing_var)
	{
		free(existing_var->value);
		existing_var->value = value;
	}
	else
		add_env_var(&cmd->export_list, name, value);
	add_or_update_env_list(&cmd->env_list, name, value);
}
