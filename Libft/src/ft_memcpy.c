/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:28:57 by keramos-          #+#    #+#             */
/*   Updated: 2023/11/21 18:15:07 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*ptr;
	char	*ptr2;

	ptr = dest;
	ptr2 = (char *)src;
	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		ptr[i] = ptr2[i];
		i++;
	}
	return (ptr);
}
