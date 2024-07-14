/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:27:05 by fibarros          #+#    #+#             */
/*   Updated: 2024/07/10 10:57:30 by fibarros         ###   ########.fr       */
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

t_env	*sort_env_list(t_env *env_list)
{
	t_env	*head;

	if (!env_list || !env_list->next)
		return (env_list);
	head = env_list;
	list_bubble_sort(head);
	return (head);
}

void	swap(t_env *a, t_env *b)
{
	char	*temp_name;
	char	*temp_value;

	temp_name = a->name;
	temp_value = a->value;
	a->name = b->name;
	a->value = b->value;
	b->name = temp_name;
	b->value = temp_value;
}

void	list_bubble_sort(t_env *head)
{
	t_env	*current;
	t_env	*last_sort;
	int		swapped;

	last_sort = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = head;
		while (current->next != last_sort)
		{
			if (ft_strcmp(current->name, current->next->name) > 0)
			{
				swap(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
		last_sort = current;
	}
}
