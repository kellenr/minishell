/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 01:41:45 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/13 00:34:33 by keramos-         ###   ########.fr       */
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
		return;
	if (head->value)
	{
		head->value = expand_env_var(head->value, msh);
	}
	token_var_exp(head->next, msh);
}

/*
 * Function to expand environment variables in a string.
 * Takes the input string and the shell structure as arguments.
 * Returns a new string with environment variables expanded.
 */
char	*expand_env_var(char *input, t_msh *msh)
{
	char	*result;
	int		i;

	if (!input)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
			result = expand_variable(input, &i, result, msh);
		else
			result = process_literal(input, &i, result);
	}
	return (result);
}

/*
 * Function to expand a variable in the input string.
 * Takes the input string, the current index, the result string, and the shell structure.
 * Returns the updated result string and updates the index.
 */
char	*expand_variable(const char *input, int *index, char *result, t_msh *msh)
{
	int j;
	char *var;
	char *expanded;
	char *tmp;

	j = *index + 1;
	if (!input[j] || (!ft_isalnum(input[j]) && input[j] != '?' && input[j] != '_'))
	{
		tmp = ft_strjoin(result, "$");
		free(result);
		*index = j;
		return tmp;
	}
	while (input[j] && (ft_isalnum(input[j]) || input[j] == '?' || input[j] == '_'))
		j++;
	var = ft_substr(input, *index, j - *index);
	expanded = expand_single_var(var, msh);
	tmp = ft_strjoin(result, expanded);
	free(result);
	free(expanded);
	free(var);
	*index = j;
	return tmp;
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
	return tmp;
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

/*
 * Function to expand a single environment variable.
 * Takes the token and the shell structure as arguments.
 * Returns the expanded value of the environment variable.
 */
char	*expand_single_var(char *token, t_msh *msh)
{
	char *key;
	char *value;

	if (ft_strcmp(token, "$?") == 0)
		return (ft_itoa(msh->exit_status));
	if (token[0] != '$')
		return (ft_strdup(token));
	key = token + 1;
	value = get_env_value(key, msh->env);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}
