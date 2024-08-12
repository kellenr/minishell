/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:27:05 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/12 21:32:53 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_token(char *token, char *error_message)
{
	if (!token)
		return (0);
	if ((token[0] == '=') || ft_isdigit(token[0]) || \
			ft_strchr(token, '\'') || ft_strchr(token, '"'))
	{
		ft_strcpy(error_message, "export `");
		ft_strcat(error_message, token);
		ft_strcat(error_message, "': not a valid identifier");
		return (0);
	}
	else
		return (1);
}

int	is_valid_export(char *token)
{
	char	error_message[100];

	ft_bzero(error_message, sizeof(error_message));
	if (!check_valid_token(token, error_message))
	{
		ft_error(error_message);
		return (0);
	}
	return (1);
}


