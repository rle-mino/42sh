/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsonetha <dsonetha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 18:29:25 by dsonetha          #+#    #+#             */
/*   Updated: 2016/06/15 15:18:39 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <grp.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <errno.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdbool.h>
# include "get_next_line.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_itoa
{
	int				neg;
	double			nb;
	int				c;
}					t_itoa;

char				**ft_cmdsplit_dquote_noslash(char const *s);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				**ft_bananasplit(char *s);
int					ft_word_counter(char *str);
char				**ft_backsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					get_next_line(int const fd, char **line);
void				quit_error(char *s);
void				quit_error_fd(char *s, int fd);
int					ft_abs(int i);
int					ft_start_str(char *start, char *s);
char				**ft_cmdsplit(char const *s);
char				*ft_strlink(char *s1, char *s2, char c);
char				*ft_strnlink(char *s1, char *s2, char c, int len);
char				*ft_str_trunc(char *str, char c);
char				*ft_sdouble_trunc(char *str, char c);
char				*no_char(char *s, char c);
char				*no_double_char(char *s, char c);
void				ft_tabdel(char **as);
char				*ft_xenostr(char *s, char c);
void				ft_putptr(void const *p);
void				ft_reverse(char *str, int len);
int					count_char(char *s, char c);
char				*ft_strndup(const char *s1, int n);
char				*ft_sjoinpath(const char *s1, const char *s2);
char				*ft_str_insert_char(char *s, char c, int i);
char				*ft_str_del_char(char *s, int i);
int					check_bracket(char *s);
char				*ft_strfill(char *s, char *fill, int off);
int					ft_isspace(char c);
char				*ft_char_to_string(char c);
bool				ft_backslash_check(char const *s, int i);
char				*epur_backslash(char *s);
char				*back_strchr(const char *s, int c);
char				*back_strchr_no_quote(const char *s, int c);

#endif
