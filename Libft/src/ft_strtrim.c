/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:33:08 by keramos-          #+#    #+#             */
/*   Updated: 2023/11/22 16:40:08 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	isset(char c, char const *set)
{
	if (!set)
		return (0);
	while (*set)
	{
		if (*set++ == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		end;
	char	*strim;

	if (!s1)
		return (0);
	i = 0;
	end = ft_strlen(s1) - 1;
	while (s1[i] && isset(s1[i], set))
		i++;
	if (!s1[i])
		return (ft_calloc(1, 1));
	while (s1[end] && isset(s1[end], set))
		end--;
	strim = ft_substr(s1, i, (end - i + 1));
	if (!strim)
		return (0);
	return (strim);
}
