/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:57:00 by fibarros          #+#    #+#             */
/*   Updated: 2024/07/09 15:06:10 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_cmd *cmd)
{
	char	**tokens;
	t_env	*env_list;
	char	*var;

	tokens = cmd->tokens;
	env_list = cmd->env_list;
	if (tokens == 0)
		print_export(env_list);
	while (tokens)
	{
		
	}
}


/*
		* if no args, print all vars;
		* if there are args, each arg should be a potential env variable to be added 
		to the linked list
		* if var already exists, we have to update the list and only if it's assigned
		if the var doesnt exist, create a new node in the envp linked list 
	
	*/

// void    sort_env_list(t_env *env_list)
// {
	
// }

// print_all_exported_vars (t_env *env)

// update env var

// create env var

// get sorted list

// void	print_export(t_env *env)
// {

// }

void print_tokens(char **tokens) 
{
	if (tokens == NULL) {
		printf("No tokens to print.\n");
		return;
	}
	for (int i = 0; tokens[i] != NULL; i++) {
		printf("Token %d: %s\n", i, tokens[i]);
	}
}
