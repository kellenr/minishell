/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:18:00 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/14 14:36:50 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to create a new token.
 * Takes the token value as an argument.
 * Returns a pointer to the new token.
 */
t_token	*create_token(char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->op = valid_op(value);
	token->next = NULL;
	return (token);
}

/*
 * Function to add a token to the end of the token list.
 * Takes a pointer to the head of the list and the token value as arguments.
 */
void	add_token(t_token **head, char *value)
{
	t_token	*new;
	t_token	*temp;

	new = create_token(value);
	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

/*
 * Function to tokenize the input string into a linked list of tokens.
 * Takes the input string as an argument.
 * Returns the head of the token list.
 */
t_token	*tokenize(char *input, t_msh *msh)
{
	t_token	*head;
	char	*token;
	int		heredoc_flag;

	heredoc_flag = 0;
	head = NULL;
	while (*input)
	{
		input = skip_spaces(input);
		if (*input)
		{
			token = extract_token(&input, msh, &heredoc_flag);
			if (!token)
			{
				free_tokens(head);
				return (NULL);
			}
			add_token(&head, token);
			free(token);
		}
		input = skip_spaces(input);
	}
	return (head);
}

/*
 * Function to extract the next token from the input string.
 * Takes a pointer to the input string as an argument and updates it.
 * Returns the extracted token.
 */
char	*extract_token(char **input, t_msh *msh, int *heredoc_flag)
{
	char	*start;
	char	*token;
	char	*cleaned_token;
	int		result;
	char	*expanded_token;

	start = *input;
	token = NULL;
	cleaned_token = NULL;
	expanded_token = NULL;
	if (is_operator(**input))
		return (handle_operator_token(input, heredoc_flag));
	result = advance_past_token(input);
	if (result == -1)
		return (NULL);
	token = ft_strndup(start, *input - start);
	if (!token)
		return (NULL);
	process_heredoc_flag(heredoc_flag, msh, token);
	expanded_token = exp_env_var(token, msh);
	free(token);
	token = expanded_token;
	cleaned_token = remove_quotes(token);
	free(token);
	return (cleaned_token);
}

/*
 * Function to remove quotes from a token.
 * Takes the token string as an argument.
 * Returns a new string without the quotes.
 */
char	*remove_quotes(const char *token)
{
	char	*output;
	int		in_single_quote;
	int		in_double_quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	output = (char *)malloc(ft_strlen(token) + 1);
	if (!output)
		return (NULL);
	while (token[i] != '\0')
	{
		if (token[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (token[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else
			output[j++] = token[i];
		i++;
	}
	output[j] = '\0';
	return (output);
}
