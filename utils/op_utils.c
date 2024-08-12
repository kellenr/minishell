/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:00:45 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/12 03:20:57 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_multi_char_op(char **input, int *heredoc_flag)
{
	if (is_multi_char_op(input, "<<"))
	{
		*heredoc_flag = 1;
		return (ft_strdup("<<"));
	}
	else if (is_multi_char_op(input, ">>"))
		return (ft_strdup(">>"));
	else if (is_multi_char_op(input, "&&"))
		return (ft_strdup("&&"));
	else if (is_multi_char_op(input, "||"))
		return (ft_strdup("||"));
	else if (**input == '(' || **input == ')')
		return (ft_strndup((*input)++, 1));
	return (NULL);
}

/*
 * Function to check if a character is an operator character.
 * Returns 1 if the character is an operator character, 0 otherwise.
 */
int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&' || c == '(' || c == ')')
		return (1);
	return (0);
}
