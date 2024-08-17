/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erro.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:19:54 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/18 00:27:26 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to print an error message and exit the program.
 * Takes an error message as an argument and prints it before exiting.
 */
void	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	prt_error(const char *format, char *arg)
{

	int	saved_stdout;

	saved_stdout = dup(1);
	dup2(2, 1);
	if (arg == NULL)
		ft_putstr_fd((char *)format, 2);
	else
		ft_printf(format, arg);
	dup2(saved_stdout, 1);
	close(saved_stdout);
}
