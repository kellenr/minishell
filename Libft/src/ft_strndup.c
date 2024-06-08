/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:24:52 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/08 20:26:58 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Function to duplicate a substring.
 * Takes the source string and the number of characters to duplicate as arguments.
 * Returns a pointer to the newly allocated string.
 */
char *ft_strndup(const char *src, size_t n)
{
	char *dst;
	size_t i;

	dst = (char *)malloc(n + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < n && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
