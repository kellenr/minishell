/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_erro.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:19:54 by keramos-          #+#    #+#             */
/*   Updated: 2024/05/28 22:25:58 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to print an error message and exit the program.
 * Takes an error message as an argument and prints it before exiting.
 */
void	ft_error(char *str)
{
	ft_printf("%s\n", str);
	exit(EXIT_FAILURE);
}
