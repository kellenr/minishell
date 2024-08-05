/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:14:19 by keramos-          #+#    #+#             */
/*   Updated: 2024/07/30 12:51:04 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to print the environment variables.
 * Takes the command structure as an argument.
 */
int	ft_env(t_cmd *cmd)
{
	char	**env;

	env = cmd->env;
	while (*env)
	{
		ft_printf("%s\n", *env);
		env++;
	}
	return (0);
}

// add error handling if there's more arguments (check if this already exists)
