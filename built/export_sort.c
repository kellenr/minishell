/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:32:09 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/19 11:42:28 by fibarros         ###   ########.fr       */
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

void	print_export(t_env *export_list)
{
	t_env	*sorted_list;

	sorted_list = sort_env_list(export_list);
	while (sorted_list != NULL)
	{
		if (sorted_list->value && *sorted_list->value)
			ft_printf("declare -x %s=\"%s\"\n", sorted_list->name, \
			sorted_list->value);
		else
			ft_printf("declare -x %s\n", sorted_list->name);
		sorted_list = sorted_list->next;
	}
}

t_env	*find_env_var(t_env *env_list, char *var)
{
	if (env_list == NULL || var == NULL)
		return (NULL);
	while (env_list)
	{
		if (ft_strcmp(env_list->name, var) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}
