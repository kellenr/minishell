/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:54:56 by fibarros          #+#    #+#             */
/*   Updated: 2024/08/19 16:05:35 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(t_ast *root, t_msh *msh)
{
	int	fd;

	fd = open_tmp_file(msh);
	if (fd == -1)
		return ;
	if (parse_heredoc(root->redir->here_doc_delim, fd, msh))
	{
		if (g_signal == 2)
			msh->exit_status = 130;
		else
			msh->exit_status = 1;
		close(fd);
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
	close(fd);
}

int	parse_heredoc(char *delimiter, int fd, t_msh *msh)
{
	char	*line;
	char	*expanded_line;

	signal(SIGINT, sig_handle_heredoc);
	while (1)
	{
		if (g_signal == 2)
			return (1);
		line = read_heredoc_line(delimiter);
		if (!line)
			break ;
		expanded_line = expand_heredoc_line(line, msh);
		if (!expanded_line)
			return (1);
		if (ft_strcmp(expanded_line, delimiter) == 0)
		{
			free(expanded_line);
			break ;
		}
		ft_putendl_fd(expanded_line, fd);
		free(expanded_line);
	}
	signal(SIGINT, sig_handler_int);
	return (0);
}

char	*read_heredoc_line(char *delimiter)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		prt_error("msh: warning: here-document delimited by end-of-file \
		(wanted %s')\n", delimiter);
		return (NULL);
	}
	return (line);
}

char	*expand_heredoc_line(char *line, t_msh *msh)
{
	char	*expanded_line;

	if (!msh->heredoc_flag)
	{
		expanded_line = exp_env_var(line, msh);
		free(line);
	}
	else
		expanded_line = line;
	return (expanded_line);
}
