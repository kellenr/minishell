/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:57:00 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/08 11:27:39 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Export function that handles exporting environment variables.
 * If no arguments are provided (`cmd->argc == 1`), prints all environment variables.
 * Otherwise, iterates through each argument to update or add environment variables.
 * Updates both the command's environment list (`cmd->env_list`) and the shell's
 * environment (`cmd->msh->env`).
 * Returns 0 on success, -1 on error.
 */
int	ft_export(t_cmd *cmd)
{
	t_env	*env_list;
	int		i;

	env_list = cmd->env_list;
	if (cmd->argc == 1)
	{
		print_export(env_list);
		return (0);
	}
	i = 1;
	while (i < cmd->argc)
	{
		if (is_valid_export(cmd->tokens[i]))
			handle_export_vars(cmd, cmd->tokens[i]);
		i++;
	}
	if (update_env_msh(cmd->msh, cmd->env_list) != 0)
	{
		perror("Error updating msh env");
		return (-1);
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
		existing_var = find_env_var(cmd->env_list, name);
		if (existing_var)
		{
			free(existing_var->value);
			existing_var->value = value;
			free(name);
			// free(value);
		}
		else
			add_env_var(&cmd->env_list, name, value);
	}
}

t_env	*find_env_var(t_env *env_list, char *var)
{
	while (env_list)
	{
		if (strcmp(env_list->name, var) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	print_export(t_env *env_list)
{
	t_env	*sorted_list;

	sorted_list = sort_env_list(env_list);
	while (sorted_list != NULL)
	{
		ft_printf("declare -x %s=\"%s\"\n", sorted_list->name, sorted_list->value);
		sorted_list = sorted_list->next;
	}
}

void	add_env_var(t_env **env_list, char *name, char *value)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
		ft_error("Memory allocation error");
	new_var->name = (name);
	new_var->value = (value);
	new_var->next = *env_list;
	*env_list = new_var;
}
