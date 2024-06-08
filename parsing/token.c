/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:18:00 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/08 22:43:16 by keramos-         ###   ########.fr       */
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
/* t_token	*tokenize(char *input)
{
	t_token	*head;
	char	*token;
	char	*pre_input;
	char	*cleaned_token;

	head = NULL;
	pre_input = process_input(input);
	token = ft_strtoke(pre_input, " ");
	while (token)
	{
		if (*token == '\'' || *token == '\"')
			cleaned_token = remove_quotes(token);
		else
			cleaned_token = ft_strdup(token);
		add_token(&head, cleaned_token);
		free(cleaned_token);
		token = ft_strtoke(NULL, " ");
	}
	free(pre_input);
	return (head);
} */

/*
 * Function to tokenize the input string into a linked list of tokens.
 * Takes the input string as an argument.
 * Returns the head of the token list.
 */
t_token	*tokenize(char *input)
{
	t_token	*head;
	char	*token;
	t_token	*temp;

	head = NULL;
	while (*input)
	{
		input = skip_spaces(input);
		if (*input)
		{
			token = extract_token(&input);
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
 * Function to skip leading spaces in the input string.
 * Takes the input string as an argument.
 * Returns the new position in the input string.
 */
char	*skip_spaces(char *input)
{
	while (*input && ft_isspace(*input))
		input++;
	return (input);
}

/*
 * Function to extract the next token from the input string.
 * Takes a pointer to the input string as an argument and updates it.
 * Returns the extracted token.
 */
char *extract_token(char **input)
{
	char	*start;
	char	*token;
	char	*cleaned_token;
	char	quote_char;

	start = *input;
	if (**input == '\'' || **input == '\"')
	{
		quote_char = *(*input)++;
		while (**input && **input != quote_char)
			(*input)++;
		if (**input == '\0') // Unmatched quote detected
			return (NULL);
		if (**input)
			(*input)++;
	}
	else
	{
		while (**input && !ft_isspace(**input) && **input != '\'' && **input != '\"')
			(*input)++;
	}
	token = ft_strndup(start, *input - start);
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
	char	*cleaned_token;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(token);
	if ((token[0] == '\'' || token[0] == '\"') && token[0] == token[len - 1])
	{
		cleaned_token = (char *)malloc(len - 1); // Allocate space for the token without outer quotes
		if (!cleaned_token)
			return (NULL);
		i = 1; // Skip the opening quote
		j = 0;
		while (i < len - 1)
			cleaned_token[j++] = token[i++];
		cleaned_token[j] = '\0';
	}
	else
		cleaned_token = ft_strndup(token, len);
	return (cleaned_token);
}
