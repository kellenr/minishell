/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:47:37 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/07 11:36:07 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_quotes(char *delimiter)
{
	size_t	len;

	len = ft_strlen(delimiter);
	if ((delimiter[0] == '\'' && delimiter[len - 1] == '\'' ) || \
		(delimiter[0] == '\"' && delimiter[len - 1] == '\"' ))
		return (1);
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

char	*handle_operator_token(char **input, int *heredoc_flag)
{
	char	*result;

	if (is_multi_char_op(input, "<<"))
	{
		*heredoc_flag = 1;
		result = (ft_strdup("<<"));
	}
	else if (is_multi_char_op(input, ">>"))
		result = (ft_strdup(">>"));
	else if (is_multi_char_op(input, "&&"))
		result = (ft_strdup("&&"));
	else if (is_multi_char_op(input, "||"))
		result = (ft_strdup("||"));
	else
	{
		(*input)++;
		result = (ft_strndup(*input - 1, 1));
	}
	if (!result)
	{
		perror("malloc fail");
		return (NULL);
	}
	return (result);
}

int	is_multi_char_op(char **input, char *op_str)
{
	int	op_len;

	op_len = ft_strlen(op_str);
	if (ft_strncmp(*input, op_str, op_len) == 0)
	{
		*input += op_len;
		return (1);
	}
	return (0);
}

int	advance_past_token(char **input)
{
	char	quote_char;

	while (**input && !ft_isspace(**input) && !is_operator(**input))
	{
		if (**input == '\'' || **input == '\"')
		{
			quote_char = *(*input)++;
			while (**input && **input != quote_char)
				(*input)++;
			if (**input == '\0')
				return (-1);
			if (**input)
				(*input)++;
		}
		else
			(*input)++;
	}
	return (0);
}
