/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:24:53 by keramos-          #+#    #+#             */
/*   Updated: 2023/12/06 16:10:08 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_str_len(int n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	if (n < 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*str;
	long	nbr;

	nbr = n;
	len = get_str_len(nbr);
	str = malloc(len + 1);
	if (!str)
		return (0);
	str[len--] = '\0';
	if (nbr < 0)
	{
		nbr = -nbr;
		str[0] = '-';
	}
	while (nbr >= 10)
	{
		str[len] = nbr % 10 + 48;
		nbr /= 10;
		len--;
	}
	str[len] = nbr % 10 + 48;
	return (str);
}
/*
int main (void)
{
	int		testCases[] = {0, 123, -456, 7890, -12345};
	int		numCases = sizeof(testCases) / sizeof(testCases[0]);
	int		i;
	char	*result;

	i = 0;
	while (i < numCases)
	{
		int n = testCases[i];
		result = ft_itoa(n);
		if (result) {
			printf("Input: %d, Output: %s\n", n, result);
			free(result);
		} else {
			printf("Input: %d, Error: Memory allocation failed\n", n);
		}
		i++;
	}
	return (0);
} */
