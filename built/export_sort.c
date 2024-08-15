/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:32:09 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/12 21:32:38 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
