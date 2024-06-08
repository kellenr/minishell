/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:14:19 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/08 14:34:14 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_cmd *cmd)
{
	char	**env;

	env = cmd->env;
	while (*env)
	{
		printf("%s\n", *env);
		 env++;
	}
}
