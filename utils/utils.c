/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:44:25 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/12 06:17:32 by keramos-         ###   ########.fr       */
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
	size_t	len;
	char	*trimmed;

	while (ft_isspace(*str))
	{
		str++;
	}
	if (*str == 0)
		return (ft_strdup(""));
	end = str + ft_strlen(str) - 1;
	while (end > str && ft_isspace(*end))
		end--;
	len = end - str + 1;
	trimmed = malloc(len + 1);
	if (!trimmed)
	{
		perror("allocation error");
		return (NULL);
	}
	ft_strncpy (trimmed, str, len);
	trimmed [len] = '\0';
	return (trimmed);
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

char	*safe_strdup(const char *s)
{
	size_t	len;
	char	*dest;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	dest = malloc(len);
	if (!dest)
	{
		ft_error("safe_strdup: malloc failed");
		return (NULL);
	}
	ft_memcpy(dest, s, len);
	return (dest);
}

void	free_ast_node(t_ast *node)
{
	int	i;

	if (node->redir)
	{
		free_redir(node->redir);
		node->redir = NULL;
	}
	if (node->command)
	{
		free(node->command);
		node->command = NULL;
	}
	if (node->args)
	{
		i = 0;
		while (node->args[i])
		{
			free(node->args[i]);
			node->args[i] = NULL;
			i++;
		}
		free(node->args);
		node->args = NULL;
	}
	free(node);
}
