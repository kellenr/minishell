/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:37:49 by keramos-          #+#    #+#             */
/*   Updated: 2024/07/17 11:00:37 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to handle redirections.
 *
 * Its important to notice that this funcion is saving the
 * STDIN_FILENO into a saved_stdin variable because we need
 * to restore it after the redirection is done. Otherwise the
 * next readline call will return NULL because the STDIN is closed.
*/
void	handle_redirection(t_ast *root, t_msh *msh)
{
	if (root->op == REDIR_INPUT)
		handle_input_redir(root, msh);
	else if (root->op == REDIR_REPLACE)
		handle_output_replace(root, msh);
	else if (root->op == REDIR_APPEND)
		handle_output_append(root, msh);
	else if (root->op == REDIR_HERE_DOC)
		handle_heredoc(root, msh);
}


void	handle_heredoc(t_ast *root, t_msh *msh)
{
	int	fd;

	fd = open_tmp_file();
	if (fd == -1)
	{
		msh->exit_status = 1;
		return ;
	}
	if (parse_heredoc(root->redir->here_doc_delim, fd))
	{
		close(fd);
		msh->exit_status = 1;
		return ;
	}
	close(fd);
	fd = open("tmp_file", O_RDONLY, 0);
	if (fd == -1)
	{
		perror("handle_heredoc: open tmp_file");
		msh->exit_status = 1;
		return ;
	}
	redirect_and_execute(fd, STDIN_FILENO, root, msh);
	unlink("tmp_file");
}

int	parse_heredoc(char *delimiter, int fd)
{
	char	*line;
	int		linenum;

	linenum = 0;
	// add g_estatus here
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf("msh: warning: here-document delimited by \
			end-of-file (wanted `%s')\n", delimiter);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
		linenum++;
	}
	// add check if g_estatus == 148 
	return (0);
}

int	open_tmp_file(void)
{
	int	fd;

	fd = open("tmp_file", O_RDWR | O_TRUNC | O_APPEND | O_CREAT, 0777);
	if (fd == -1)
		ft_error("Parsing error");
	return (fd);
}
