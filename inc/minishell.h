/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:43:39 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/28 20:00:39 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/wait.h>

/* # include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h> */

# define MAX_TKS 1024

/* COLOR intro */
# define RT			"\033[0m"
# define P_G		"\033[38;2;186;255;201m"
# define P_B		"\033[1;38;2;186;225;255m"
# define P_L		"\033[38;2;255;186;255m"
# define P_M		"\033[1;38;5;183m"
# define P_P		"\033[1;38;2;255;209;220m"
# define P_R		"\033[38;2;255;179;186m"

// Enumeration for different operators
typedef enum e_op
{
	NONE,
	PIPE,
	REDIR_APPEND,
	REDIR_REPLACE,
	REDIR_HERE_DOC,
	REDIR_INPUT,
	AND,
	OR
}		t_op;

/*
 * Structure representing the minishell.
 * The minishell structure is used to store information about the shell
 * environment, such as environment variables and the exit status.
 * Members:
 * - env: Array of environment variables.
 * - exit_status: The exit status of the last executed command.
 */
typedef struct s_msh
{
	char	**env;
	int		exit_status;
}		t_msh;

/*
 * Structure representing a command to be executed.
 * The command structure is used to store detailed information about a command,
 * including its arguments and environment variables, for execution purposes.
 * Members:
 * - cmd: The command name (e.g., "echo").
 * - tokens: Array of argument strings. This includes the command itself and
 * its arguments.
 * - env: Array of environment variables relevant to the command.
 * - argc: The number of arguments in the tokens array.
 * - next: Pointer to the next command in a pipeline. This is used to chain
 * commands together.
 * - prev: Pointer to the previous command in a pipeline.
 */
typedef struct s_cmd
{
	char			*cmd;
	char			**tokens;
	t_msh			*msh;
	char			**env;
	int				argc;
	int				exit_status;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}		t_cmd;

/*
 * Structure representing a node in the Abstract Syntax Tree (AST).
 * The AST is used to represent the hierarchical structure of commands
 * and operators (such as pipes and redirections) in the shell input.
 * Members:
 * -The value of the node. This can be a cmd, an argument, or an op (e.g., "|").
 * -Pointer to the left child node. This typically represents the l side of an op
 * or a sub-cmd.
 * -Pointer to the right child node. This typically represents the r side of an
 * op or a sub-cmdd.
 */
typedef struct s_ast
{
	char			*value;
	t_op			op;
	struct s_ast	*left;
	struct s_ast	*right;
}		t_ast;

/*
 * Structure representing a token in the input string.
 * Tokens are used to break down the input string into manageable parts
 * (e.g., commands, arguments, operators) before constructing the AST.
 * Members:
 * -The value of the token. This can be a part of a command, an argument,
 * or an operator.
 * -Pointer to the next token in the linked list.
 */
typedef struct s_token
{
	char			*value;
	t_op			op;
	int				quoted;
	struct s_token	*next;
}		t_token;

/* ************************************************************************** */
/*                                 SOURCES                                    */
/* ************************************************************************** */

/*                               handel msg                                   */

void	ft_intro_art(void);
void	receive_msg(t_msh *msh);
char	*read_input(void);

/*                                  utlis                                     */

int		ft_isspace(char c);
char	*trim_whitespace(char *str);
int		cmp_s(const char *str1, const char *str2);
t_op	valid_op(const char *operator);
int		is_builtin(char *cmd);
void	ft_error(char *str);
void	free_cmd(t_cmd *cmd);
void	free_tokens(t_token *tokens);
void	free_ast(t_ast *root);
char	*remove_quotes(const char *token);
char	*skip_spaces(char *input);
int		is_number(const char *str);
char	*get_dir(t_cmd *cmd, char *prev_dir);

char	*find_path(char *cmd, char **env);
char	*get_path(char *cmd, char **paths);

/*                                   BUILT                                    */

int		ft_echo(t_cmd *scmd);
int		ft_pwd(void);
int		ft_cd(t_cmd *cmd);
int		ft_env(t_cmd *cmd);
void	ft_exit(t_cmd *cmd);

/*                                  Parsing                                   */

t_token	*create_token(char *value, int single);
void	add_token(t_token **head, char *value, int single);
t_token	*tokenize(char *input);
char	*extract_token(char **input, int *single);
t_ast	*create_ast_node(char *value, t_op op);
t_ast	*init_ast(t_token **tokens);
t_ast	*handle_non_operator(t_token **current_token, t_ast *current_node);
t_ast	*handle_operator_ast(t_token **current_token, t_ast *root);
t_ast	*parse_tokens_to_ast(t_token *tokens);
t_ast	*create_operator_node(t_token **current_token, t_ast *ast_node);
t_ast	*handle_child(t_token **current_token, t_ast *current_right);
void	handle_remaining_tokens(t_token **token, t_ast *right);

/*                                    src                                     */

char	*process_input(const char *input);
void	handle_quotes(const char **inp_ptr, char **res_ptr);
void	handle_operator(const char **inp_ptr, char **res_ptr);
t_cmd	*ast_to_cmd(t_ast *root);
void	process_cmd(char *prompt, t_msh *msh);
void	execute_ast(t_ast *root, t_msh *msh);
void	execute_command(t_cmd *cmd);
int		execute_builtin(t_cmd *cmd);
int		count_ast_nodes(t_ast *root);
void	populate_tokens_array(t_ast *root, char **tokens, int *index);

/*                                    module                                  */
char	*exp_env_var(char *input, t_msh *msh);
char	*exp_variable(const char *input, int *index, char *result, t_msh *msh);
char	*process_literal(const char *input, int *index, char *result);
char	*get_env_value(char *var, char **env);
void	token_var_exp(t_token *head, t_msh *msh);
char	*exp_single_var(char *token, t_msh *msh);
char	*exp_special_var(const char *input, int *index, char *result, t_msh *msh);
char	*exp_general_var(const char *input, int *index, char *result, t_msh *msh);

/*                                    pipes                                  */
pid_t	fork_first_child(t_ast *root, t_msh *msh, int pipefd[2]);
pid_t	fork_second_child(t_ast *root, t_msh *msh, int pipefd[2]);
void	execute_pipe(t_ast *root, t_msh *msh);

// Redirection Handling Functions
//void	handle_redirection(t_ast *root, t_msh *msh);

// Background Execution Functions
//void	handle_background(t_ast *root, t_msh *msh);
void	print_ast(t_ast *root, int level, char *branch);
#endif
