/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:56:29 by keramos-          #+#    #+#             */
/*   Updated: 2024/05/11 00:03:43 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	type_var(char *c, va_list element, int *count)
{
	if (*c == 'c')
		ft_put_c(va_arg(element, int), count);
	if (*c == 's')
		ft_put_s(va_arg(element, char *), count);
	if (*c == 'p')
		ft_put_p(va_arg(element, void *), count);
	if (*c == 'd' || *c == 'i')
		ft_put_nbr(va_arg(element, int), count);
	if (*c == 'u')
		ft_put_u(va_arg(element, unsigned int), count);
	if (*c == 'x')
		ft_hexa_x(va_arg(element, unsigned int), count);
	if (*c == 'X')
		ft_hexa_cap_x(va_arg(element, unsigned int), count);
	else if (*c == '%')
		ft_put_c(*c, count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	if (!format)
		return (-1);
	while (*format)
	{
		if (*format == '%')
		{
			type_var((char *)++format, args, &count);
		}
		else
			ft_put_c(*format, &count);
		format++;
	}
	va_end(args);
	return (count);
}
