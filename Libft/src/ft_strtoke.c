/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoke.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:09:07 by keramos-          #+#    #+#             */
/*   Updated: 2024/05/25 22:30:58 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ft_strtoke:
*	this function mimics the behavior of the standard strtok function.
*	breaks the string str into a series of tokens using the delimiter delim.
 */
char	*ft_strtoke(char *str, const char *delim)
{
	static char	*static_str;
	char		*start;

	if (str != NULL)
		static_str = str;
	if (static_str == NULL || *static_str == '\0')
		return (NULL);
	while (*static_str && ft_strchr(delim, *static_str) != NULL)
		static_str++;
	if (*static_str == '\0')
		return (NULL);
	start = static_str;
	while (*static_str && ft_strchr(delim, *static_str) == NULL)
		static_str++;
	if (*static_str)
	{
		*static_str = '\0';
		static_str++;
	}
	return (start);
}

/*
int main(void)
{
	char str[80] = "This is - www.tutorialspoint.com - website";
	const char s[2] = "-";
	char *token;

	// get the first token
	token = ft_strtoke(str, s);

	// walk through other tokens
	while ( token != NULL )
	{
		printf( " %s\n", token );
		token = ft_strtoke(NULL, s);
	}
	return(0);
} */
