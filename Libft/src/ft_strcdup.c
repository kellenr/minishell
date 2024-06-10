/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:09:12 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/10 02:09:51 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function to duplicate a string until a certain character.
 * Takes the string and the character as arguments.
 * Returns the duplicated string.
 */
char	*ft_strcdup(const char *s, int c)
{
	char	*dup;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	dup = ft_substr(s, 0, i);
	return (dup);
}
