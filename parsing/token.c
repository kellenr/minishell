/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:18:00 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/19 09:57:49 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function to create a new token.
 * Takes the token value as an argument.
 * Returns a pointer to the new token.
 */
t_token	*create_token(char *value, bool quoted_flag)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (quoted_flag)
		token->op = NONE;
	else
		token->op = valid_op(value);
	token->next = NULL;
	token->broken = false;
	return (token);
}

/*
 * Function to add a token to the end of the token list.
 * Takes a pointer to the head of the list and the token value as arguments.
 */
void	add_token(t_token **head, char *value, bool quoted_flag)
{
	t_token	*new;
	t_token	*temp;

	new = create_token(value, quoted_flag);
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
	bool	quoted_flag;

	heredoc_flag = 0;
	head = NULL;
	while (*input)
	{
		quoted_flag = false;
		input = skip_spaces(input);
		if (*input)
		{
			token = extract_token(&input, msh, &heredoc_flag, &quoted_flag);
			if (!token)
			{
				add_token(&head, "", false);
				head->broken = true;
				return (head);
			}
			if (ft_strlen(token) > 0)
				add_token(&head, token, quoted_flag);
			free(token);
		}
		input = skip_spaces(input);
	}
	return (head);
}

/*
 * extract_token - Extracts the next token from the input string.
 * @input: A pointer to the input string. The function advances this pointer
 *         to the next position after the extracted token.
 * @msh: A pointer to the main shell structure, used for environment variables
 *       and other shell-specific data.
 * @heredoc_flag: A pointer to an integer that indicates if the current command
 *                involves a heredoc operation.
 * @quoted_flag: A pointer to a boolean that indicates if the token is within
 *               quotes (single or double).
 * Return: A pointer to the extracted token, with any environment variables
 * expanded
 *         and quotes removed. The caller is responsible for freeing the
 * returned string.
 * This function is responsible for extracting the next meaningful token
 * from the input string.
 * A token is a sequence of characters that can represent a command, an
 * argument, or an operator.
 * The function handles various cases, including quoted strings, environment
 * variable expansion,
 * and operators like `|`, `>`, `<`, `>>`, and `<<`.
 * Edge Cases and Detailed Behavior:
 * 1. **Null or Empty Input**:
 *    - If `*input` is NULL or points to an empty string (`""`), the function
 * returns NULL.
 *    - This prevents dereferencing a NULL pointer or operating on an empty
 * string.
 * 2. **Quoted Strings**:
 *    - The function checks if the current token starts with a single quote
 * (`'`) or a double quote (`"`).
 *    - The condition `if ((*input[0] == '\'' || *input[0] == '\"') &&
 * ft_strlen(*input) > 1 && ((*input)[1] != (*input)[0]))`
 *      is particularly important:
 *      - `(*input[0] == '\'' || *input[0] == '\"')`: Checks if the first
 * character of the token is a single or double quote.
 *      - `ft_strlen(*input) > 1`: Ensures that the string has more than one
 * character. This check avoids falsely setting `quoted_flag`
 *        for cases where the input string is just a single quote or double
 * quote (e.g., `"'`). If the string is only a quote, it is likely an error
 * or incomplete input.
 *      - `((*input)[1] != (*input)[0]))`: Ensures that the second character
 * is not the same as the first character (e.g., `" "` or `''`). This prevents
 * setting the
 *        `quoted_flag` if the input is something like `" "`, which is an edge
 * case where the quotes are empty or just contain spaces. If the input contains
 * matching quotes
 *        at the beginning and end without any other characters in between, the
 * quotes are effectively treated as an empty string.
 *    - If all these conditions are met, the `quoted_flag` is set to `true`,
 * indicating that the token is a quoted string.
 *    - The function then skips the quotes, extracts the content, and removes
 * the quotes before returning the token.
 * 3. **Operators**:
 *    - If `*quoted_flag` is `false`, the function checks if the current token
 * is an operator using `is_operator(**input)`.
 *    - If it is an operator, the function handles it separately and returns
 * the operator as a token.
 * 4. **Token Extraction**:
 *    - The `advance_past_token` function is called to move the `*input`
 * pointer past the current token.
 *    - The length of the token is calculated by the difference between the
 * initial position (`start`) and the new position of `*input`.
 *    - The token is then duplicated using `ft_strndup`, ensuring that only the
 * characters belonging to the token are copied.
 * 5. **Heredoc Flag Processing**:
 *    - After extracting the token, the function checks if it involves a
 * heredoc (`<<`) operation using `process_heredoc_flag`.
 *    - The `heredoc_flag` is updated accordingly.
 * 6. **Environment Variable Expansion**:
 *    - The function then expands any environment variables within the token
 * using `exp_env_var`.
 *    - If environment variables are present, their values replace the variable
 * names in the token.
 * 7. **Quote Removal**:
 *    - After processing the token, any remaining quotes are removed using
 * `remove_quotes`.
 *    - This ensures that the returned token is clean and ready for use by
 * the shell.
 * 8. **Memory Management**:
 *    - The function allocates memory for the token, expanded token, and
 * cleaned token using `ft_strndup`, `ft_strdup`, or similar functions.
 *    - The caller is responsible for freeing the returned token to avoid
 * memory leaks.
 *    - Intermediate tokens are freed appropriately within the function to
 * avoid unnecessary memory consumption.
*/
char	*extract_token(char **input, t_msh *msh, int *heredoc_flag, bool *quoted_flag)
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
	if ((*input[0] == '\'' || *input[0] == '\"') && ft_strlen(*input) > 1 && ((*input)[1] != (*input)[0]))
		*quoted_flag = true;
	if (*quoted_flag == false && is_operator(**input))
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
