/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:54:56 by fibarros          #+#    #+#             */
/*   Updated: 2024/07/22 17:43:39 by fibarros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(t_ast *root, t_msh *msh)
{
	int	fd;

	fd = open_tmp_file();
	if (fd == -1)
	{
		msh->exit_status = 1;
		return ;
	}
	if (parse_heredoc(root->redir->here_doc_delim, fd, msh))
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
	close(fd);
}

int	parse_heredoc(char *delimiter, int fd, t_msh *msh)
{
	char	*line;
	// int		linenum;
	char	*expanded_line;

	// linenum = 0;
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
		expanded_line = exp_env_var(line, msh);
		free(line);
		if (!expanded_line)
			return (1);
		if (ft_strcmp(expanded_line, delimiter) == 0)
		{
			free(expanded_line);
			break ;
		}
		ft_putendl_fd(expanded_line, fd);
		free(expanded_line);
		// linenum++;
	}
	// add check if g_estatus == 148
	return (0);
}

int	process_heredoc_lines(char *delim, int fd, t_msh *msh, int expand_vars)
{
	char	*line;
	char	*expanded_line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf("msh: warning: here-document delimited by \
			end-of-file (wanted `%s')\n", delim);
			break ;
		}
		if (expand_vars)
		{
			expanded_line = exp_env_var(line, msh);
			free(line);
			if (!expanded_line)
				return (1);
		}
		else
			expanded_line = line;
		if (ft_strcmp(expanded_line, delim) == 0)
		{
			free(expanded_line);
			break ;
		}
		ft_putendl_fd(expanded_line, fd);
		if (expand_vars)
			free(expanded_line);
	}
}
