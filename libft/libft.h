/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 19:29:59 by darian            #+#    #+#             */
/*   Updated: 2022/09/13 11:53:19 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct s_vector2D
{
	int	x;
	int	y;
}	t_vector2D;

typedef struct s_vector3D
{
	int	x;
	int	y;
	int	z;
}	t_vector3D;

typedef struct s_vector4D
{
	int	x;
	int	y;
	int	z;
	int	w;
}	t_vector4D;

typedef struct s_list
{
	void			*content;
	void			*result;
	struct s_list	*next;
}	t_list;

typedef struct s_alloc
{
	void			*ptr;
	struct s_alloc	*next;
}	t_alloc;

void		ft_malloc_clear(t_alloc **lst);
void		*ft_malloc(int size, t_alloc	**lst);
void		*ft_realloc(void *buf, int old_size, int new_size, t_alloc	**lst);
int			ft_body_2(t_vector4D *it, char **split, char const *s,
				t_alloc *alloc);
char		*ft_strncpy_split_quote(char const *src, size_t n, t_alloc *alloc);

int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strstr(const char *haystack, const char *needle);
char		**ft_split_export(char const *s, char c, t_alloc *alloc);
char		**ft_split(char const *s, char c, t_alloc **alloc);
char		**ft_split_quote(char const *s, char c, t_alloc *alloc);
char		*ft_strncpy(char *dest, char const *src, size_t n);
int			ft_strncmp(char const *s1, char const *s2, size_t n);
char		*ft_strncat(char *dest, char const *src, size_t n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char),
				t_alloc *alloc);
size_t		ft_strlen(const char *s);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strcat(char *dest, const char *src);
void		ft_putstr_fd(char const *str, int fd);
void		ft_putnbr_fd(int nb, int fd);
void		ft_putendl_fd(char const *str, int fd);
void		ft_putchar_fd(char c, int fd);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
char		*ft_itoa(int n, t_alloc *alloc);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
void		ft_bzero(void *s, size_t n);
int			ft_atoi(const char *nptr);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strdup(const char *s, t_alloc **alloc);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strjoin(char const *s1, char const *s2, t_alloc **alloc);
char		*ft_strjoin_char(char const *s1, char const s2, t_alloc **alloc);
void		*ft_calloc(size_t count, size_t size, t_alloc *alloc);
int			ft_isprint(int c);
int			ft_isascii(int c);
size_t		ft_strlcpy(char *dst, const char *src,
				size_t dstsize);
char		**my_split(char const *s, char c);
char		*my_strdup(const char *src);
char		*my_strjoin(char const *s1, char const*s2);
char		*ft_strtrim(char const *s1, char const *set, t_alloc *alloc);
char		*ft_substr(char const *s, unsigned int start, size_t len,
				t_alloc *alloc);
void		ft_intset(int *tab, int size, int nb);

t_list		*ft_lstnew(void *content, t_alloc **alloc);
void		ft_lstadd_front(t_list **alst, t_list *new);
void		ft_lstadd_index(t_list **alst, t_list *new, int index);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *),
				t_alloc *alloc);
int			ft_strcmp(char const *s1, char const *s2);
int			is_backed(char *str, int i);
int			ft_strisdigit(char *str);
u_int64_t	ft_atoi_u64(char *nptr);
char		*ft_lol(char *str[2], t_vector2D *quote, t_vector2D *last_q,
				t_vector2D *it);

#endif