/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:10:35 by keramos-          #+#    #+#             */
/*   Updated: 2024/07/03 17:02:51 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to expand environment variables in a list of tokens.
 * Takes the head of the token list and the shell structure as arguments.
 * Expands environment variables in each token's value.
 */
void	token_var_exp(t_token *head, t_msh *msh)
{
	if (!head)
		return ;
	if (head->value && !head->quoted)
	{
		head->value = exp_env_var(head->value, msh);
	}
	token_var_exp(head->next, msh);
}

/*
 * Function to process a literal part of the input string.
 * Takes the input string, the current index, and the result string.
 * Returns the updated result string and updates the index.
 */
char	*process_literal(const char *input, int *index, char *result)
{
	int j;
	char *literal;
	char *tmp;

	j = *index;
	while (input[j] && input[j] != '$')
		j++;
	literal = ft_substr(input, *index, j - *index);
	tmp = ft_strjoin(result, literal);
	free(result);
	free(literal);
	*index = j;
	return (tmp);
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
		if (ft_strncmp(*env, var, ft_strlen(var)) == 0 && \
				(*env)[ft_strlen(var)] == '=')
			return (*env + ft_strlen(var) + 1);
		env++;
	}
	return (NULL);
}
