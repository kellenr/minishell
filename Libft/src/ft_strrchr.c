/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:01:31 by keramos-          #+#    #+#             */
/*   Updated: 2023/11/21 18:17:36 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	unsigned char	b;

	b = (unsigned char)c;
	i = ft_strlen(s);
	while (i + 1)
	{
		if (s[i] == b)
			return ((char *)&s[i]);
		i--;
	}
	return (0);
}
