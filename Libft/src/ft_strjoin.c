/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:10:33 by keramos-          #+#    #+#             */
/*   Updated: 2023/11/22 12:29:07 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	len;
	unsigned int	i;
	char			*str;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (*s1)
			str[i++] = *s1++;
	}
	if (s2)
	{
		while (*s2)
			str[i++] = *s2++;
	}
	str[i] = '\0';
	return (str);
}
