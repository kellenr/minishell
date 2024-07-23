/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:54:56 by fibarros          #+#    #+#             */
/*   Updated: 2024/07/23 11:34:02 by fibarros         ###   ########.fr       */
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
	int		linenum;
	char	*expanded_line;
	int		expand_vars;

	linenum = 0;
	expand_vars = !has_quotes(delimiter);
	// add g_estatus here
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf("msh: warning: here-document delimited by \
			end-of-file (wanted %s')\n", delimiter);
			break ;
		}
		if (expand_vars)
		{
			expanded_line = exp_env_var(line, msh);
			free(line);
		}
		else
			expanded_line = line;
		if (!expanded_line)
			return (1);
		if (ft_strcmp(expanded_line, delimiter) == 0)
		{
			free(expanded_line);
			break ;
		}
		ft_putendl_fd(expanded_line, fd);
		free(expanded_line);
		linenum++;
	}
	// add check if g_estatus == 148
	return (0);
}










// int	parse_heredoc(char *delimiter, int fd, t_msh *msh)
// {
// 	char	*trimmed_delimiter;
// 	int		result;
// 	int		expand_vars;

// 	// add g_estatus here
// 	expand_vars = !has_quotes(delimiter);
// 	if (expand_vars)
// 	{
// 		trimmed_delimiter = strip_quotes(delimiter);
// 		if (!trimmed_delimiter)
// 			return (1);
// 	}
// 	else
// 	{
// 		trimmed_delimiter = ft_strdup(delimiter);
// 		if (!trimmed_delimiter)
// 			return (1);
// 	}
// 	result = process_heredoc_lines(trimmed_delimiter, fd, msh);
// 	free(trimmed_delimiter);
// 	return (result);
// }

// int	process_heredoc_lines(char *delimiter, int fd, t_msh *msh)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 		{
// 			ft_printf("msh: warning: here-document delimited by \
// 			end-of-file (wanted `%s')\n", delimiter);
// 			return (0);
// 		}
// 		if (handle_line(line, delimiter, fd, msh))
// 			return (1);
// 	}
// 	return (0);
// }

// int	handle_line(char *line, char *delimiter, int fd, t_msh *msh)
// {
// 	char	*expanded_line;

// 	expanded_line = line;
// 	if (!has_quotes(delimiter))
// 	{
// 		expanded_line = exp_env_var(line, msh);
// 		free(line);
// 		if (!expanded_line)
// 			return (1);
// 	}
// 	if (ft_strcmp(expanded_line, delimiter) == 0)
// 	{
// 		free(expanded_line);
// 		return (0);
// 	}
// 	ft_putendl_fd(expanded_line, fd);
// 	if (expanded_line != line)
// 		free(expanded_line);
// 	return (0);
// }
