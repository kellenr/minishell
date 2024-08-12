/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:00:32 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/12 15:03:04 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_empty_prompt(char *prompt, char **trimmed_prompt)
{
	if (!prompt || !*prompt)
		return ;
	*trimmed_prompt = trim_whitespace(prompt);
	if (!trimmed_prompt || !*trimmed_prompt)
	{
		free(*trimmed_prompt);
		*trimmed_prompt = NULL;
	}
}

void	handle_preprocessing(char *trimmed_prompt, char **preprocessed_input)
{
	if (!trimmed_prompt)
		return ;
	*preprocessed_input = process_input(trimmed_prompt);
	if (!preprocessed_input)
		ft_error("Error: failed to process input");
}
