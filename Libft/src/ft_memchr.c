/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:06:23 by keramos-          #+#    #+#             */
/*   Updated: 2023/11/21 18:37:00 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s1;
	unsigned char	b;

	s1 = (unsigned char *)s;
	b = (unsigned char)c;
	while (n--)
	{
		if (*s1 == b)
			return ((void *)s1);
		s1++;
	}
	return (0);
}
