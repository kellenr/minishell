/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_v3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:27:48 by fibarros          #+#    #+#             */
/*   Updated: 2024/07/17 14:27:59 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_var_end(char *str, int index)
{
	int	end_index;

	end_index = index;
	while (str[end_index] && (ft_isalnum(str[end_index]) \
		|| str[end_index] == '_'))
		end_index++;
	return (end_index);
}

