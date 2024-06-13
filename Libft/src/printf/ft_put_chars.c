/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_chars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:13:51 by keramos-          #+#    #+#             */
/*   Updated: 2024/02/06 16:56:05 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_null(char *s, int *count)
{
	while (*s)
		ft_put_c(*s++, count);
}

void	ft_put_c(char c, int *count)
{
	ft_putchar_fd(c, 1);
	(*count)++;
}

void	ft_put_s(char *s, int *count)
{
	int	i;

	i = 0;
	if (!s)
	{
		ft_put_null("(null)", count);
		return ;
	}
	while (s[i])
	{
		ft_put_c(s[i], count);
		i++;
	}
}
