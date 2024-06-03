/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:47:32 by keramos-          #+#    #+#             */
/*   Updated: 2024/01/24 17:06:25 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

/* ---------- GET_NEXT_LINE -------------------- */

char	*get_next_line(int fd);

/* ---------- UTILS -------------------- */

char	*ft_strjoin(char *s1, char *s2);
void	*ft_calloc(size_t count, size_t size);

#endif
