/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kellenr <kellenr@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:25:41 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/15 13:21:19 by kellenr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to get the value of an environment variable.
 * Takes the variable and the environment variables as arguments.
 * Returns the value of the variable.
 */
char	*get_expanded_value(char *token, t_msh *msh)
{
	char	*key;
	char	*value;

	if (ft_strcmp(token, "$?") == 0)
		return (ft_itoa(msh->exit_status));
	else if (token[0] != '$')
		return (ft_strdup(token));
	else
	{
		key = token + 1;
		value = get_env_value(key, msh->env);
		if (value)
			return (ft_strdup(value));
		else
			return (ft_strdup(""));
	}
}

/*
 * Function to expand a single environment variable.
 * Takes the token and the shell structure as arguments.
 * Returns the expanded value of the variable.
 * Frees the token.
 * Returns NULL on malloc failure.
 */
char	*exp_single_var(char *token, t_msh *msh)
{
	char	*result;

	result = get_expanded_value(token, msh);
	if (!result)
	{
		perror("malloc fail");
		free(token);
		return (NULL);
	}
	free(token);
	return (result);
}

/*
 * Function to combine the expanded variable with the rest of the string.
 * Takes the expanded variable and the rest of the string as arguments.
 * Frees the expanded variable and the rest of the string.
 * Returns the combined string.
 * Returns NULL on malloc failure.
 */
char	*combine_expanded_with_rest(char *expanded, char *rst)
{
	char	*tmp;

	tmp = ft_strjoin(rst, expanded);
	// free(rst);
	free(expanded);
	if (!tmp)
		return (NULL);
	return (tmp);
}

/*
 * Function to extract and expand a variable.
 * Takes the input string, the current index, and the shell
 * structure as arguments.
 * Returns the expanded variable.
 * Updates the index.
 * Returns NULL on malloc failure.
 */
char	*ext_and_exp_var(const char *input, int *index, t_msh *msh)
{
	int		j;
	char	*var;
	char	*expanded;

	j = *index + 1;
	while (input[j] && (ft_isalnum(input[j]) || input[j] == '?' \
		|| input[j] == '_'))
		j++;
	var = ft_substr(input, *index, j - *index);
	if (!var)
		return (NULL);
	if (is_var_btw_squote(input, *index, j))
	{
		expanded = ft_strdup(var);
		free(var);
	}
	else
		expanded = exp_single_var(var, msh);
	if (!expanded)
		return (NULL);
	*index = j;
	return (expanded);
}
