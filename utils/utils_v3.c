/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_v3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:27:48 by fibarros          #+#    #+#             */
/*   Updated: 2024/07/22 17:38:45 by fibarros         ###   ########.fr       */
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

char	*strip_quotes(char *delimiter)
{
	size_t	len;

	len = ft_strlen(delimiter);
	if (has_quotes(delimiter))
		return (ft_substr(delimiter, 1, len - 2));
	return (ft_strdup(delimiter));
}
