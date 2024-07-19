/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibarros <fibarros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:54:56 by fibarros          #+#    #+#             */
/*   Updated: 2024/07/17 14:38:53 by fibarros         ###   ########.fr       */
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
	close(fd);
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

char	*expand_vars(char *line, t_msh *msh)
{
	char	*new_line;
	int		i;
	int		start_index;
	int		end_index;

	i = 0;
	new_line = ft_strdup(line);
	if (!new_line)
		return (NULL);
	while (new_line[i])
	{
		if (new_line[i] == '$' && new_line[i + 1] != '\0')
		{
			start_index = i;
			end_index = find_var_end(new_line, i + 1);
			if (end_index > start_index + 1)
			{
				if (process_var(new_line, start_index, end_index, msh))
					return (NULL);
			}
			i = end_index - 1;
		}
		i++;
	}
	return (new_line);
}

int	*expand_and_replace_var(char *ptr, char *var_name, t_msh *msh)
{
	char	*env_value;
	size_t	var_len;
	size_t	env_len;
	size_t	remaining_len;

	env_value = get_env_value(var_name, msh->env);
	if (!env_value)
		return (1);
	var_len = ft_strlen(var_name);
	env_len = ft_strlen(env_value);
	remaining_len = ft_strlen(ptr + 1);
	ft_memmove(ptr, env_value, env_len);
	ft_memmove(ptr + env_len, ptr + var_len + 1, remaining_len + 1);
	free(env_value);
	return (0);
}

int	process_var(char *new_line, int start_index, int end_index, t_msh *msh)
{
	char	*var_name;

	var_name = (char *)malloc((end_index - start_index) * sizeof(char));
	if (!var_name)
	{
		perror("malloc failed");
		return (1);
	}
	strncpy(var_name, &new_line[start_index + 1], end_index - start_index - 1);
	var_name[end_index - start_index - 1] = '\0';
	if (expand_and_replace_var(&new_line[start_index], var_name, msh))
	{
		free(var_name);
		free(new_line);
		return (1);
	}
	free(var_name);
	return (0);
}
