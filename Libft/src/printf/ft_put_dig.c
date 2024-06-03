/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_dig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:14:05 by keramos-          #+#    #+#             */
/*   Updated: 2024/02/06 16:56:10 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_nbr(int n, int *count)
{
	if (n == -2147483648)
	{
		ft_put_s("-2147483648", count);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		ft_put_c('-', count);
	}
	if (n >= 10)
		ft_put_nbr(n / 10, count);
	ft_put_c(n % 10 + '0', count);
}

void	ft_u_put_nbr(unsigned int u, int *count)
{
	if (u >= 10)
		ft_u_put_nbr(u / 10, count);
	ft_put_c(u % 10 + '0', count);
}

void	ft_put_u(unsigned int u, int *count)
{
	ft_u_put_nbr(u, count);
}
