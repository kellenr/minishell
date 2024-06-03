/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:27:39 by keramos-          #+#    #+#             */
/*   Updated: 2024/02/06 16:56:15 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_hexa(unsigned int num, char *format, int *count)
{
	if (num >= 16)
		ft_put_hexa(num / 16, format, count);
	ft_put_c(format[num % 16], count);
}

void	ft_hexa_x(unsigned int num, int *count)
{
	ft_put_hexa(num, "0123456789abcdef", count);
}

void	ft_hexa_cap_x(unsigned int num, int *count)
{
	ft_put_hexa(num, "0123456789ABCDEF", count);
}
