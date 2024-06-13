/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keramos- <keramos-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:34:20 by keramos-          #+#    #+#             */
/*   Updated: 2024/06/10 02:10:37 by keramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdarg.h>
# include <stdint.h>

/* ************************************************************************** */
/*                                 STRUCT                                     */
/* ************************************************************************** */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* ************************************************************************** */
/*                                  CHECK                                     */
/* ************************************************************************** */

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);

/* ************************************************************************** */
/*                                 MEMORY                                     */
/* ************************************************************************** */

void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);

/* ************************************************************************** */
/*                                   LIST                                     */
/* ************************************************************************** */

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void*));

/* ************************************************************************** */
/*                                  PRINT                                     */
/* ************************************************************************** */

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/* ************************************************************************** */
/*                                 STRING                                     */
/* ************************************************************************** */

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *src, size_t n);
char	*ft_strcdup(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strtoke(char *str, const char *delim);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		ft_atoi(const char *str);
int		ft_toupper(int c);
int		ft_tolower(int c);

/* ************************************************************************** */
/*                                 PRINTF                                     */
/* ************************************************************************** */

int		ft_printf(const char *format, ...);

/* ------------------------------ PRINTERS ---------------------------------- */

void	ft_put_c(char c, int *count);
void	ft_put_s(char *s, int *count);
void	ft_put_null(char *s, int *count);
void	ft_put_nbr(int n, int *count);
void	ft_put_u(unsigned int nb, int *count);
void	ft_u_put_nbr(unsigned int u, int *count);
void	ft_put_hexa(unsigned int num, char *format, int *count);
void	ft_hexa_x(unsigned int num, int *count);
void	ft_hexa_cap_x(unsigned int num, int *count);
void	ft_put_pad(uintptr_t pad, char *hex, int *count);
void	ft_put_p(void *ptr, int *count);
void	type_var(char *c, va_list element, int *count);
void	ft_put_f(double f, int *count);

/* ************************************************************************** */
/*                                   GNL                                      */
/* ************************************************************************** */

char	*get_next_line(int fd);

/* ************************************************************************** */
/*                                  Extra                                     */
/* ************************************************************************** */

void	handle_errors(char *error_msg);

#endif
