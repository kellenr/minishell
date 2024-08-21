/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:43:39 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/22 01:37:23 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/stat.h>

/* # include <sys/types.h>

# include <dirent.h>
 */

# define MAX_TKS 1024
# define MAX_ARGUMENTS 100
# define BUFFER_MULTIPLIER 3

/* COLOR intro */
# define RT			"\033[0m"
# define P_G		"\033[38;2;186;255;201m"
# define P_B		"\033[1;38;2;186;225;255m"
# define P_L		"\033[38;2;255;186;255m"
# define P_M		"\033[1;38;5;183m"
# define P_P		"\033[1;38;2;255;209;220m"
# define P_R		"\033[38;2;255;179;186m"

#define M_HANDLE_REDIRECTION_FILE(tmp, tmpfd) \
do { \
	if (tmp->op == REDIR_APPEND) \
		tmpfd = open(tmp->redir->append_file, O_WRONLY | O_CREAT | O_APPEND, 0644); \
	else \
		tmpfd = open(tmp->redir->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644); \
	close(tmpfd); \
} while (0)

// Enumeration for different operators
typedef enum e_op
{
	NONE,
	PIPE,
	REDIR_INPUT,
	REDIR_REPLACE,
	REDIR_APPEND,
	REDIR_HERE_DOC,
	AND,
	OR,
	SUBSHELL,
	OPEN,
	CLOSE
}		t_op;

/*env list*/

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}		t_env;

/*
 * Structure representing a redirection.
 * The redirection structure is used to store information about redirections
 * in the shell input, such as input/output files and here-doc delimiters.
 * Members:
 * - input_file: The name of the input file for '<' redirection.
 * - output_file: The name of the output file for '>' redirection.
 * - append_file: The name of the append file for '>>' redirection.
 * - here_doc_delim: The delimiter for '<<' redirection.
 */
typedef struct s_redir
{
	char	*input_file;
	char	*output_file;
	char	*append_file;
	char	*here_doc_delim;
}		t_redir;

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
	int		heredoc_flag;
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
	t_env			*env_list;
	t_env			*export_list;
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
	char			*command;
	char			**args;
	t_op			op;
	t_redir			*redir;
	int				fd;
	int				saved_fd;
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
	bool			broken;
}		t_token;

typedef struct s_ast_pointers
{
	t_ast	**cur_node;
	t_ast	**root;
	t_ast	**pthesis_node;
} t_ast_ptrs;

/* ************************************************************************** */
/*                                 SOURCES                                    */
/* ************************************************************************** */

extern volatile __sig_atomic_t	g_signal;

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
void	print_with_escapes(const char *str);
char	*find_path(char *cmd, char **env);
char	*get_path(char *cmd, char **paths);
int		is_var_btw_squote(const char *input, int start, int end);
int		update_env_msh(t_msh *msh, t_env *env_list);
char	**list_to_array(t_env *env_list);
char	**populate_env_array(t_env *env_list, char **env_array, int list_size);
void	free_array(char **arr, int size);
int		init_msh(char **env, t_msh *msh);
t_ast	*init_ast_node(void);
void	initialize_command_and_args(t_ast *node, t_token *token);
bool	is_op_token(t_token *token);
t_ast	*process_token(t_token **token, t_ast *root, t_ast *current_node);
char	*handle_operator_token(char **input, int *heredoc_flag);
int		is_multi_char_op(char **input, char *op_str);
int		advance_past_token(char **input);
t_cmd	*init_cmd(void);
char	**copy_tokens(char **args, int *count);
void	free_msh(t_msh *msh);
void	free_all(t_msh *msh);
void	free_redir(t_redir *redir);
char	*handle_parenthesis(char **input);
char	*get_multi_char_op(char **input, int *heredoc_flag);
void	free_ast_node(t_ast *node);
int		handle_malloc_failure(t_ast *node, const char *error_message);
t_ast	*free_redir_node(t_redir *redir, t_ast *node);
void	fork_and_execute(t_cmd *cmd, char *cmd_path);
void	execute_command_helper(t_ast *root, t_msh *msh);
void	parse_and_execute(t_token *tokens, t_msh *msh);
void	format_error_message(char *error_message, char *token);
char	*expand_or_process_literal(char *input, int *i, char *result, \
		t_msh *msh);
char	*initialize_result_and_tmp(char **tmp);
void	init_vars_ast(t_ast **root, t_ast **cur_node, t_token **cur_token, \
		t_token *tokens);
void	init_ext_vars( char **token, char **clean_token, char **input, \
		bool *quoted_flag);
char	*process_new_token(t_token **head, char *input, t_msh *msh, \
		int *heredoc_flag);
char	*trim_and_validate_prompt(char *prompt);

/*					Exec utils					*/
char	*get_command_path(t_cmd *cmd, int *allocated);
void	execute_in_child(char *cmd_path, char **tokens, char **env);
void	handle_child_status(t_cmd *cmd, int status);
int		check_tokens(t_cmd *cmd);

/*									ENV										  */
int		init_env(t_cmd *cmd, char **envp);
int		init_arr_and_list(t_cmd *cmd, char **envp);
t_env	*create_env_node(const char *env_str);
void	add_env_node(t_env **env_list, t_env *node);
int		array_len(char **arr);
void	free_env(t_cmd *cmd);
void	free_env_list(t_env *env_list);
int		parse_env_str(const char *env_str, char **name, char **value);
int		init_env_and_export(t_cmd *cmd, char **envp);
int		find_path_var(char **env);
char	*ft_getenv(char *name, t_cmd *cmd);

/*                                   BUILT                                    */

int		ft_echo(t_cmd *scmd);
int		ft_pwd(void);
int		ft_cd(t_cmd *cmd);
int		ft_env(t_cmd *cmd);
void	ft_exit(t_cmd *cmd);
int		ft_export(t_cmd *cmd);
int		ft_unset(t_cmd *cmd);

/*									BUILT UTILS								  */
int		check_valid_token(char *token);
int		is_valid_export(char *token);
t_env	*sort_env_list(t_env *env_list);
void	swap(t_env *a, t_env *b);
void	list_bubble_sort(t_env *head);
void	print_export(t_env *env_list);
void	handle_export_vars(t_cmd *cmd, char *arg);
t_env	*find_env_var(t_env *env_list, char *var);
void	add_env_var(t_env **env_list, char *name, char *value);
int		is_valid_unset(char *token);
int		check_valid_unset_token(char *token, char *error_message);
void	remove_env_var(t_env **env_list, char *name);
void	initialize_echo(bool *flg, bool *eflg, int *i);
void	parse_options(t_cmd *scmd, int *i, bool *flg, bool *eflg);
void	add_or_update_env_list(t_env **env_list, char *name, char *value);
void	handle_var_assignment(t_cmd *cmd, char *name, char *value);

/*                                  Parsing                                   */

t_token	*create_token(char *value, bool quoted_flag);
void	add_token(t_token **head, char *value, bool quoted_flag);
t_token	*tokenize(char *input, t_msh *msh);
char	*extract_token(char **input, t_msh *msh, int *heredoc_flag, bool *quoted_flag);
t_ast	*init_ast(t_token **current_token);
t_ast	*handle_non_operator(t_token **current_token, t_ast *current_node);
t_ast	*handle_operator_ast(t_token **current_token, t_ast *root, t_msh *msh);
t_ast	*parse_tokens_to_ast(t_token *tokens, t_msh *msh);
int		set_command_and_args(t_ast *node, t_token *current_token);
t_ast	*create_ast_node(void);
t_ast	*handle_pthesis_tk(t_token **cur_token, t_ast **root, t_ast **cur_node);
t_ast	*handle_op_and_non_op_tokens(t_token *cur_token, t_ast *root);
void	handle_token_op(t_token **cur_token, t_ast **cur_node, t_ast **root, \
		t_ast **pthesis_node, t_msh *msh);
void	*free_ast_return_null(t_ast *cur_node);
void	*handle_nop_block(t_token **cur_token, t_ast **cur_node, t_ast **root);

/*                                    src                                     */

char	*process_input(const char *input);
void	handle_quotes(const char **inp_ptr, char **res_ptr);
void	handle_operator(const char **inp_ptr, char **res_ptr, char *result, \
size_t buffer_size);
t_cmd	*ast_to_cmd(t_ast *root);
void	process_cmd(char *prompt, t_msh *msh);
void	execute_ast(t_ast *root, t_msh *msh);
void	execute_command(t_cmd *cmd);
int		execute_builtin(t_cmd *cmd);
int		count_ast_nodes(t_ast *root);
void	populate_tokens_array(t_ast *root, char **tokens, int *index);
void	*handle_buffer_overflow(const char *error_message);
void	free_null(char *str);

/*                                    module                                  */
char	*exp_env_var(char *input, t_msh *msh);
char	*exp_variable(const char *input, int *index, char *result, t_msh *msh);
char	*process_literal(const char *input, int *index, char *result);
char	*get_env_value(char *var, char **env);
void	token_var_exp(t_token *head, t_msh *msh);
char	*exp_single_var(char *token, t_msh *msh);
char	*exp_special_var(const char *input, int *index, char *rst, t_msh *msh);
char	*exp_general_var(const char *input, int *index, char *rst, t_msh *msh);
void	handle_logical_op(t_ast *root, t_msh *msh);
void	handle_parentheses_op(t_ast *root, t_msh *msh);
t_ast	*parse_parentheses(t_token **current_token, t_msh *msh);
t_ast	*integrate_ast_node(t_ast *root, t_ast *pthesis_node);
t_ast	*handle_parentheses_ast(t_token **current_token, t_ast *root, \
		t_msh *msh);
char	*extract_and_expand_var(const char *input, int *index, t_msh *msh);
char	*const_final_exp(char *exp, const char *input, int *index, char *rst);
char	*get_expanded_value(char *token, t_msh *msh);
char	*ext_and_exp_var(const char *input, int *index, t_msh *msh);
char	*combine_expanded_with_rest(char *expanded, char *rst);
char	*expand_command(t_cmd *cmd);
char	*handle_path_search(char *expanded_cmd, t_cmd *cmd, int *allocated);
char	*process_path_stat(char *expanded_cmd, struct stat *path_stat, \
		t_cmd *cmd, int *allocated);

/*                                    pipes                                  */
pid_t	fork_first_child(t_ast *root, t_msh *msh, int pipefd[2]);
pid_t	fork_first_child_heredoc(t_ast *root, t_msh *msh, int pipefd[2], \
		int heredoc_fd);
pid_t	fork_second_child(t_ast *root, t_msh *msh, int pipefd[2]);
void	execute_pipes(t_ast *root, t_msh *msh);
void	wait_for_childs(pid_t p1, pid_t p2, int pipefd[2], t_msh *msh);

t_ast	*get_command(t_ast *root, int *current_index, int target_index);
int		count_commands(t_ast *root);

int		is_operator(char c);

// Redirection Handling Functions
void	handle_redirection(t_ast *root, t_msh *msh);
t_ast	*handle_operator_redir_ast(t_token **current_token, t_ast *root);
t_redir	*init_redir(void);

// Logical Execution Functions
t_ast	*handle_operator_and_or_ast(t_token **current_token, t_ast *root);

void	print_ast(t_ast *node);
void	print_pipe(t_ast *node, int level, const char *label);

char	*safe_strdup(const char *s);

/*									REDIR UTILS								*/
void	handle_input_redir(t_ast *root, t_msh *msh);
void	handle_output_replace(t_ast *root, t_msh *msh);
void	handle_output_append(t_ast *root, t_msh *msh);
int		handle_fd_redirection(int fd, int target_fd);
void	redirect_and_execute(int fd, int std_fd, t_ast *root, t_msh *msh);
int		open_tmp_file(t_msh *msh);
int		parse_heredoc(char *delimiter, int fd, t_msh *msh);
void	handle_heredoc(t_ast *root, t_msh *msh);
t_ast	*create_redir_node(int op, t_ast *root);
void	handle_redir_file(t_token **current_token, char **file_field);
int		has_quotes(char *delimiter);
char	*read_heredoc_line(char *delimiter);
char	*expand_heredoc_line(char *line, t_msh *msh);
void	process_heredoc_flag(int *heredoc_flag, t_msh *msh, char *token);
int		handle_redir_input(t_token **current_token, t_ast *redir_node);
int		handle_redir_replace(t_token **current_token, t_ast *redir_node);
int		handle_redir_append(t_token **current_token, t_ast *redir_node);
int		handle_redir_heredoc(t_token **current_token, t_ast *redir_node);
void	process_heredoc_flag(int *heredoc_flag, t_msh *msh, char *token);
bool	check_input_file(t_ast *root, t_msh *msh);
bool	check_redir_has_command(t_ast *root, t_msh *msh);
void	handle_multiple_redir_files(t_ast *root);
int		handle_heredoc_pipe(t_ast *root, t_msh *msh);

/*									SIGNALS								*/
void	sig_handler_int(int signum);
void	handle_signals(void);
void	sig_non_interactive(int signum);
void	handle_non_interactive(void);
void	sig_handle_heredoc(int signum);
void	setup_signal_handlers(void);
// void	heredoc_sig_handler(int signum, siginfo_t *info, void *context);
// void	handle_signals_heredoc(void);

//////////// 	TEST	////////
// void	print_tokens(char **tokens);
void	print_env_list(t_env *env_list);
// void test_create_env_node();
// void test_add_env_node();
// void test_init_arr_and_list();
// void test_init_env();
void	prt_error(const char *format, char *arg);
void	handle_multiple_outputs(t_ast *root, t_msh *msh);

#endif
