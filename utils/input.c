/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:34:23 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/02 14:17:46 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*Read input:
*	This function use the readline function and let us give a name to or prompt.
*	and then we verifies that input points to some memory location (input).
*	and then we check if the value pointed to by input is not zero
*	Essentially, it verifies that input is not an empty string (*input).
 */
char	*read_input(void)
{
	char	*input;

	input = readline(P_L "🌸 Minishel" RT "-> ");
	if (input && *input)
		add_history(input);
	return (input);
}
