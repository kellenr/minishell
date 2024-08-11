/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:32:36 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/07 10:16:54 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to preprocess the input string.
 * Handles quotes and operators, preparing the input for tokenization.
 */
char	*process_input(const char *input)
{
	char		*result;
	char		*res_ptr;
	const char	*inp_ptr;

	result = malloc(strlen(input) * 2);
	if (!result)
	{
		perror("allocation error");
		return (NULL);
	}
	res_ptr = result;
	inp_ptr = input;
	while (*inp_ptr)
	{
		if (*inp_ptr == '\'' || *inp_ptr == '\"')
			handle_quotes(&inp_ptr, &res_ptr);
		else if (valid_op(inp_ptr) != NONE)
			handle_operator(&inp_ptr, &res_ptr);
		else
			*res_ptr++ = *inp_ptr++;
	}
	*res_ptr = '\0';
	return (result);
}

/*
 * Function to handle quoted strings in the input.
 * Copies the quoted content to the result pointer, handling escape characters
 * if necessary.
 */
void	handle_quotes(const char **inp_ptr, char **res_ptr)
{
	char	quote;

	quote = **inp_ptr;
	*(*res_ptr)++ = *(*inp_ptr)++;
	while (**inp_ptr && **inp_ptr != quote)
	{
		if (**inp_ptr == '\\' && (*(*inp_ptr + 1) == quote \
			|| *(*inp_ptr + 1) == '\\'))
			*(*res_ptr)++ = *(*inp_ptr)++;
		*(*res_ptr)++ = *(*inp_ptr)++;
	}
	if (**inp_ptr == quote)
		*(*res_ptr)++ = *(*inp_ptr)++;
}

/*
 * Function to handle operators in the input.
 * Surrounds operators with spaces to make tokenization easier.
 */
void	handle_operator(const char **inp_ptr, char **res_ptr)
{
	t_op	op;

	op = valid_op(*inp_ptr);
	if (op != NONE)
	{
		*(*res_ptr)++ = ' ';
		while (**inp_ptr && !ft_isspace(**inp_ptr) && **inp_ptr != '\0')
		{
			*(*res_ptr)++ = *(*inp_ptr)++;
		}
		*(*res_ptr)++ = ' ';
	}
}
