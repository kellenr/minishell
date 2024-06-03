/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:44:25 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/02 19:29:13 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to check if a character is a whitespace character.
 * Returns 1 if the character is a whitespace character, 0 otherwise.
 */
int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

/*
 * Function to trim leading and trailing whitespace from a string.
 * Returns a pointer to the trimmed string.
 * Note: This function modifies the input string.
 */
char	*trim_whitespace(char *str)
{
	char	*end;

	while (ft_isspace(*str))
		str++;
	if (*str == 0)
		return (str);
	end = str + strlen(str) - 1;
	while (end > str && ft_isspace(*end))
		end--;
	*(end + 1) = '\0';
	return (str);
}

/*
 * Function to compare two strings for equality.
 * Returns 0 if the strings are equal, a non-zero value otherwise.
 */
int	cmp_s(const char *str1, const char *str2)
{
	size_t	i;

	if ((str1 && !str2) || (!str1 && str2))
		return (1);
	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	return (0);
}

/*
 * Function to remove surrounding quotes from a string.
 * Takes a string with possible surrounding quotes.
 * Returns a new string with the quotes removed.
 */
char	*remove_quotes(char *str)
{
	int len = ft_strlen(str);
	if ((str[0] == '"' && str[len - 1] == '"') || \
		(str[0] == '\'' && str[len - 1] == '\''))
	{
		char *new_str = ft_substr(str, 1, len - 2);
		return (new_str);
	}
	return (ft_strdup(str));
}
