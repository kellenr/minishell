/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:32:36 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/12 05:39:13 by keramos-         ###   ########.fr       */
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
	size_t		buffer_size;
	size_t		input_len;

	input_len = ft_strlen(input);
	buffer_size = input_len * BUFFER_MULTIPLIER + 10;
	result = malloc(buffer_size);
	if (!result)
		handle_buffer_overflow("allocation error");
	res_ptr = result;
	inp_ptr = input;
	while (*inp_ptr)
	{
		if (*inp_ptr == '\'' || *inp_ptr == '\"')
			handle_quotes(&inp_ptr, &res_ptr);
		else if (valid_op(inp_ptr) != NONE)
			handle_operator(&inp_ptr, &res_ptr, result, buffer_size);
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
void	handle_operator(const char **inp_ptr, char **res_ptr, char *result, \
size_t buffer_size)
{
	t_op		op;
	size_t		needed_space;
	const char	*temp;

	needed_space = 0;
	op = valid_op(*inp_ptr);
	if (op != NONE)
	{
		temp = *inp_ptr;
		while (**inp_ptr && !ft_isspace(*temp) && *temp != '\0')
		{
			needed_space++;
			temp++;
		}
		needed_space += 3;
		if ((*res_ptr - result) + needed_space >= buffer_size)
			handle_buffer_overflow("buffer overflow prevented");
		*(*res_ptr)++ = ' ';
		while (**inp_ptr && !ft_isspace(**inp_ptr) && **inp_ptr != '\0')
			*(*res_ptr)++ = *(*inp_ptr)++;
		*(*res_ptr)++ = ' ';
	}
	**res_ptr = '\0';
}

void	*handle_buffer_overflow(const char *error_message)
{
	perror(error_message);
	return (NULL);
}
