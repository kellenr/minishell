/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 00:16:43 by keramos-          #+#    #+#             */
/*   Updated: 2024/08/23 00:25:59 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_file(int src_fd, int dest_fd)
{
	ssize_t	bytes_read;
	ssize_t	bytes_written;
	char	buffer[1024];

	while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0)
	{
		bytes_written = write(dest_fd, buffer, bytes_read);
		if (bytes_written != bytes_read)
			return -1;
	}
	if (bytes_read < 0)
		return -1;
	return 0;
}

t_hrd	new_heredoc_redir(t_ast *root, t_msh *msh)
{
	t_hrd	heredoc_redir;

	if (root->op == REDIR_REPLACE)
	{
		heredoc_redir.open_flags = (O_WRONLY | O_CREAT | O_TRUNC);
		heredoc_redir.output_file = root->redir->output_file;
	}
	else
	{
		heredoc_redir.open_flags = (O_WRONLY | O_CREAT | O_APPEND);
		heredoc_redir.output_file = root->redir->append_file;
	}
	heredoc_redir.open_mode = 0777;
	heredoc_redir.heredoc_fd = parse_and_get_heredoc_fd(root->left, msh);
	return heredoc_redir;
}


int	handle_heredoc_output_redir(t_ast *root, t_msh *msh)
{
	int		output_fd;
	t_hrd	hdocr;

	hdocr = new_heredoc_redir(root, msh);

	if (hdocr.heredoc_fd == -1)
		return (-1);
	output_fd = open(hdocr.output_file, hdocr.open_flags, hdocr.open_mode);
	if (output_fd < 0)
	{
		msh->exit_status = errno;
		close(hdocr.heredoc_fd);
		return -1;
	}
	if (copy_file(hdocr.heredoc_fd, output_fd) == -1)
	{
		msh->exit_status = errno;
		close(hdocr.heredoc_fd);
		close(output_fd);
		return -1;
	}
	close(hdocr.heredoc_fd);
	close(output_fd);
	return (0);
}
