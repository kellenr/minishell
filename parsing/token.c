/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:18:00 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/02 19:19:37 by keramos-         ###   ########.fr       */
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
t_token	*tokenize(char *input)
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
		cleaned_token = remove_quotes(token);
		add_token(&head, cleaned_token);
		free(cleaned_token);
		token = ft_strtoke(NULL, " ");
	}
	free(pre_input);
	return (head);
}

/*
 * Function to convert a linked list of tokens to an array of strings.
 * Takes the head of the token list as an argument.
 * Returns an array of strings.
 */
/* char	**tokens_to_array(t_token *tokens)
{
	char	**array;
	int		count;
	t_token	*temp;

	temp = tokens;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	count = 0;
	while (tokens)
	{
		array[count++] = ft_strdup(tokens->value);
		tokens = tokens->next;
	}
	array[count] = NULL;
	return (array);
} */
