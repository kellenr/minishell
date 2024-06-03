/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:24:40 by keramos-          #+#    #+#             */
/*   Updated: 2023/11/21 18:16:26 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	b;

	b = (unsigned char)c;
	while (*s)
	{
		if (*s == b)
			return ((char *)s);
		s++;
	}
	if (b == '\0')
		return ((char *)s);
	return (0);
}
