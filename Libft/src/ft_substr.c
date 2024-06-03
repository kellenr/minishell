/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:05:20 by keramos-          #+#    #+#             */
/*   Updated: 2023/11/28 18:33:08 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	slen;

	slen = len;
	if (start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	if (start + slen > ft_strlen(s))
	{
		slen = (ft_strlen(s) - start);
	}
	sub = (char *)malloc(slen + 1);
	if (!sub)
		return (0);
	i = 0;
	while (i < slen)
	{
		sub[i] = s[i + start];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
