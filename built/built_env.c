/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kellenr <kellenr@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:14:19 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/15 12:19:24 by kellenr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to print the environment variables.
 * Takes the command structure as an argument.
 */
int	ft_env(t_cmd *cmd)
{
	if (cmd->argc > 1)
	{
		ft_printf("msh: env: no arguments supported\n");
		return (1);
	}
	print_env_list(cmd->env_list);
	return (0);
}
