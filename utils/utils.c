/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:44:25 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/09 20:30:18 by keramos-         ###   ########.fr       */
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
	end = str + ft_strlen(str) - 1;
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
 * Function to skip leading spaces in the input string.
 * Takes the input string as an argument.
 * Returns the new position in the input string.
 */
char	*skip_spaces(char *input)
{
	while (*input && ft_isspace(*input))
		input++;
	return (input);
}
