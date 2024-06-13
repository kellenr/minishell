/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:47:32 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/10 01:03:51 by keramos-         ###   ########.fr       */
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
# include "libft.h"

/* ---------- GET_NEXT_LINE -------------------- */

char	*get_next_line(int fd);

/* ---------- UTILS -------------------- */

char	*ft_strjoins(char *s1, char *s2);
void	*ft_callocs(size_t count, size_t size);

#endif
