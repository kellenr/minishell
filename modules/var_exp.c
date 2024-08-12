/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 01:41:45 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/11 23:40:55 by keramos-         ###   ########.fr       */
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
	if (!result)
		return (NULL);
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
 * Function to handle the general case of variable expansion.
 * Takes the input string, the current index, the result string, and the
 * shell structure.
 * Returns the updated result string and updates the index.
 */
char	*exp_general_var(const char *input, int *index, char *rst, t_msh *msh)
{
	char	*expanded;

	expanded = ext_and_exp_var(input, index, msh);
	if (!expanded)
	{
		free(rst);
		return (NULL);
	}
	return (combine_expanded_with_rest(expanded, rst));
}

/*
 * Function to expand a variable in the input string.
 * Takes the input string, the current index, the result string,
 * and the shell structure.
 * Returns the updated result string and updates the index.
 */
char	*exp_variable(const char *input, int *index, char *result, t_msh *msh)
{
	int		j;
	char	*expanded;

	j = *index + 1;
	if (input[j] == '\0' || input[j] == ' ')
	{
		expanded = ft_strjoin(result, "$");
		(*index)++;
		return (expanded);
	}
	if (input[j] == '?')
	{
		expanded = exp_special_var(input, index, result, msh);
		return (expanded);
	}
	expanded = exp_general_var(input, index, result, msh);
	return (expanded);
}

/*
 * Function to process a literal in the input string.
 * Takes the input string, the current index, and the result string.
 * Returns the updated result string and updates the index.
 */
char	*const_final_exp(char *exp, const char *input, int *index, char *rst)
{
	char	*suffix;
	char	*tmp;
	char	*final_expansion;

	suffix = ft_substr(input, *index + 2, *index - (*index + 2));
	if (!suffix)
		return (NULL);
	tmp = ft_strjoin(exp, suffix);
	free(suffix);
	free(exp);
	if (!tmp)
		return (NULL);
	final_expansion = ft_strjoin(rst, tmp);
	free(rst);
	free(tmp);
	if (!final_expansion)
		return (NULL);
	return (final_expansion);
}

/*
 * Function to expand special variables in the input string.
 * Takes the input string, the current index, the result string,
 * and the shell structure.
 * Returns the updated result string and updates the index.
 * Special variables are $?. They are expanded to the exit status of the last
 * command.
 */
char	*exp_special_var(const char *input, int *index, char *rst, t_msh *msh)
{
	char	*exp;

	exp = extract_and_expand_var(input, index, msh);
	if (!exp)
		return (NULL);
	return (const_final_exp(exp, input, index, rst));
}
