/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 01:41:45 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/12 23:27:58 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to expand environment variables.
 * Takes the command structure as an argument.
 */
/* void	var_exp(t_ast *root, char **env) */
/* { */


/* 	if (!root) */
/* 		return ; */
/* 	if (root->value) */
/* 	{ */
/* 		root->value = expand_env_var(root->value, env); */
/* 	} */
/* 	var_exp(root->left, env); */
/* 	var_exp(root->right, env); */
/* } */

/*
 * Function to expand environment variables in a token list.
 */
void token_var_exp(t_token *head, t_msh *msh)
{
	if (!head)
		return ;
	if (head->value)
	{
		head->value = expand_env_var(head->value, msh);
	}
	token_var_exp(head->next, msh);
}

/*
 * Function to expand a single environment variable.
 * Takes the token and the environment variables as arguments.
 * Returns the expanded token.
 */
char	*expand_env_var(char *token, t_msh *msh)
{
	char *key;
	char *value;

	if (token[0] == '$' && token[1] == '?')
		return ft_itoa(msh->exit_status);

	if (token[0] != '$')
		return (ft_strdup(token));

	key = token + 1; // Skip the '$'
	value = get_env_value(key, msh->env);

	if (value)
		return (ft_strdup(value));

	return (ft_strdup(""));
}

/*
 * Function to get the value of an environment variable.
 * Takes the variable and the environment variables as arguments.
 * Returns the value of the variable.
 */
char	*get_env_value(char *var, char **env)
{
	while (*env)
	{
		if (ft_strncmp(*env, var, ft_strlen(var)) == 0 && (*env)[ft_strlen(var)] == '=')
			return (*env + ft_strlen(var) + 1);
		env++;
	}
	return (NULL);
}
