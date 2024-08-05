/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:47:37 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/05 16:48:22 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_quotes(char *delimiter)
{
	size_t	len;

	len = ft_strlen(delimiter);
	if ((delimiter[0] == '\'' && delimiter[len - 1] == '\'' ) || \
		(delimiter[0] == '\"' && delimiter[len - 1] == '\"' ))
		return (1);
	return (0);
}

/*
 * Function to skip leading spaces in the input string.
 * Takes the input string as an argument.
 * Returns the new position in the input string.
 */
char	*skip_spaces(char *input)
{
	while (*input && ft_isspace(*input))
		input++;
	return (input);
}
