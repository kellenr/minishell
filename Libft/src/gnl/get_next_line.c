/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:47:26 by keramos-          #+#    #+#             */
/*   Updated: 2024/01/24 17:07:28 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	copy_s2_in_s1(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}

static int	find_line(char *buf, char **line)
{
	int		i;
	int		j;
	int		flag_line;
	char	*find_line;

	i = 0;
	j = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	flag_line = 0;
	if (buf[i] == '\n')
		flag_line = 1;
	find_line = ft_calloc(i + flag_line + 1, 1);
	if (find_line == NULL)
		return (-1);
	while (j < i + flag_line)
	{
		find_line[j] = buf[j];
		j++;
	}
	*line = ft_strjoin(*line, find_line);
	if (*line == NULL)
		return (-1);
	copy_s2_in_s1(buf, &buf[i + flag_line]);
	return (flag_line);
}

static char	*free_line(char **line)
{
	if (*line)
		free(*line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			count_byte;
	int			flag_line;

	line = NULL;
	flag_line = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (flag_line == 0)
	{
		flag_line = find_line(buf, &line);
		if (flag_line == -1)
			return (free_line(&line));
		if (flag_line == 0)
		{
			count_byte = read(fd, buf, BUFFER_SIZE);
			if (count_byte == 0 && *line)
				flag_line = 1;
			else if (count_byte <= 0)
				return (free_line(&line));
			buf[count_byte] = '\0';
		}
	}
	return (line);
}
