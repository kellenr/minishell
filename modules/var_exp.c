/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 01:41:45 by keramos-          #+#    #+#             */
/*   Updated: 2024/07/22 15:53:15 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to expand environment variables in a string.
 * Takes the input string and the shell structure as arguments.
 * Returns a new string with environment variables expanded.
 */
char	*exp_env_var(char *input, t_msh *msh)
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
			result = exp_variable(input, &i, result, msh);
		else
			result = process_literal(input, &i, result);
	}
	return (result);
}

/*
 * Function to handle the special variable $? and any following suffix.
 * Takes the input string, the current index, the result string, and the
 * shell structure.
 * Returns the updated result string and updates the index.
 */
char	*exp_special_var(const char *input, int *index, char *rst, t_msh *msh)
{
	int		j;
	char	*var;
	char	*expanded;
	char	*suffix;
	char	*tmp;

	j = *index + 2;
	var = ft_substr(input, *index, 2);
	expanded = exp_single_var(var, msh);
	free(var);
	while (input[j] && (ft_isalnum(input[j]) || input[j] == '?' \
			|| input[j] == '_' || input[j] == '$'))
		j++;
	suffix = ft_substr(input, *index + 2, j - (*index + 2));
	tmp = ft_strjoin(expanded, suffix);
	free(expanded);
	free(suffix);
	expanded = ft_strjoin(rst, tmp);
	free(rst);
	free(tmp);
	*index = j;
	return (expanded);
}

/*
 * Function to handle the general case of variable expansion.
 * Takes the input string, the current index, the result string, and the
 * shell structure.
 * Returns the updated result string and updates the index.
 */
char	*exp_general_var(const char *input, int *index, char *rst, t_msh *msh)
{
	int		j;
	char	*var;
	char	*expanded;
	char	*tmp;

	j = *index + 1;
	while (input[j] && (ft_isalnum(input[j]) || input[j] == '?' \
			|| input[j] == '_'))
		j++;
	var = ft_substr(input, *index, j - *index);
	expanded = exp_single_var(var, msh);
	tmp = ft_strjoin(rst, expanded);
	free(rst);
	free(expanded);
	free(var);
	*index = j;
	return (tmp);
}

/*
 * Function to expand a variable in the input string.
 * Takes the input string, the current index, the result string,
 * and the shell structure.
 * Returns the updated result string and updates the index.
 */
char	*exp_variable(const char *input, int *index, char *result, t_msh *msh)
{
	int	j;

	j = *index + 1;
	if (input[j] == '\0' || input[j] == ' ')
	{
		result = ft_strjoin(result, "$");
		(*index)++;
		return (result);
	}
	if (input[j] == '?')
		return (exp_special_var(input, index, result, msh));
	return (exp_general_var(input, index, result, msh));
}

/*
 * Function to expand a single environment variable.
 * Takes the token and the shell structure as arguments.
 * Returns the expanded value of the environment variable.
 */
char	*exp_single_var(char *token, t_msh *msh)
{
	char	*key;
	char	*value;

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
