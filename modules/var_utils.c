/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:10:35 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/20 22:17:46 by keramos-         ###   ########.fr       */
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
	int		j;
	char	*literal;
	char	*tmp;

	j = *index;
	while (input[j] && input[j] != '$')
		j++;
	literal = ft_substr(input, *index, j - *index);
	if (!literal)
	{
		free(result);
		return (NULL);
	}
	tmp = ft_strjoin(result, literal);
	if (!tmp)
	{
		free(result);
		free(literal);
		return (NULL);
	}
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

int	is_var_btw_squote(const char *input, int start, int end)
{
	int	i;
	int	in_single_q;
	int	in_double_q;

	i = 0;
	in_single_q = 0;
	in_double_q = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '"' && !in_single_q)
			in_double_q = !in_double_q;
		if (input[i] == '\'' && !in_double_q)
			in_single_q = !in_single_q;
		if (i == start && in_single_q)
			return (1);
		if (i > end)
			break ;
		i++;
	}
	return (0);
}

char	*extract_and_expand_var(const char *input, int *index, t_msh *msh)
{
	char	*var;
	char	*expanded;

	var = ft_substr(input, *index, 2);
	if (!var)
		return (NULL);
	expanded = exp_single_var(var, msh);
	if (!expanded)
		return (NULL);
	return (expanded);
}
