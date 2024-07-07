/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:20:52 by keramos-          #+#    #+#             */
/*   Updated: 2024/07/07 15:59:54 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to check if a string is a valid option for the echo command.
 * Validates the -n option where n can appear multiple times.
 * Returns true if the string is a valid option, false otherwise.
 */
bool	check_opt(char *s)
{
	if (!*s)
		return (false);
	if (*s == '-' && *(s + 1))
	{
		s++;
		while (*s == 'n' || *s == 'e')
			s++;
	}
	if (*s)
		return (false);
	return (true);
}

/*
 * Function to print a string with escape sequences.
 */
void	print_with_escapes(const char *str)
{
	while (*str)
	{
		if (*str == '\\' && *(str + 1))
		{
			str++;
			if (*str == 'n')
				ft_printf("\n");
			else if (*str == 't')
				ft_printf("\t");
			else
			{
				ft_printf("\\");
				ft_printf("%c", *str);
			}
		}
		else
			ft_printf("%c", *str);
		str++;
	}
}

/*
 * Function to print arguments to the standard output.
 * Handles the -n option to omit the trailing newline.
 * Iterates through the arguments and prints them separated by spaces.
 * Prints a newline at the end if the -n option is not specified.
 * Returns 0 on completion.
 */
int	ft_echo(t_cmd *scmd)
{
	bool	flg;
	bool	eflg;
	int		i;

	i = 1;
	flg = false;
	eflg = false;
	while (scmd->tokens[i] && check_opt(scmd->tokens[i]))
	{
		if (scmd->tokens[i][1] == 'n')
			flg = true;
		else if (scmd->tokens[i][1] == 'e')
			eflg = true;
		i++;
	}
	while (scmd->tokens[i])
	{
		if (eflg)
			print_with_escapes(scmd->tokens[i]);
		else
			ft_printf("%s", scmd->tokens[i]);
		if (scmd->tokens[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!flg)
		ft_printf("\n");
	return (0);
}
