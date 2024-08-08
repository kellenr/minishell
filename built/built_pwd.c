/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:33:02 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/08 11:31:05 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to print the current working directory.
 * Uses getcwd to get the directory and prints it.
 * Returns EXIT_SUCCESS on success.
 */
int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_error(P_R"Error."RT);
	}
	ft_printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
