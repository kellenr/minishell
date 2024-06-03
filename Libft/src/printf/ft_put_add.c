/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:30:11 by keramos-          #+#    #+#             */
/*   Updated: 2024/02/06 16:56:00 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_pad(uintptr_t pad, char *hex, int *count)
{
	if (pad >= 16)
		ft_put_pad(pad / 16, hex, count);
	ft_put_c(hex[pad % 16], count);
}

void	ft_put_p(void *ptr, int *count)
{
	uintptr_t	pad;

	pad = (uintptr_t)ptr;
	if (!pad)
	{
		ft_put_s("(nil)", count);
		return ;
	}
	ft_put_s("0x", count);
	ft_put_pad(pad, "0123456789abcdef", count);
}
