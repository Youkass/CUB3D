/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:47:05 by darian            #+#    #+#             */
/*   Updated: 2022/09/13 11:53:13 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	count_words_quote(char const *s, char c)
{
	int	i;
	int	w;
	int	d_quoted;
	int	s_quoted;

	i = 0;
	w = 0;
	s_quoted = 0;
	d_quoted = 0;
	while (s[i])
	{
		if (s[i] == '"' && !is_backed((char *)s, i - 1) && !s_quoted)
			d_quoted = (d_quoted + 1) % 2;
		if (s[i] == '\'' && !d_quoted)
			s_quoted = (s_quoted + 1) % 2;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0)
			&& (!s_quoted && !d_quoted))
			w++;
		i++;
	}
	return (w);
}

char	*ft_strncpy_split_quote(char const *src, size_t n, t_alloc *alloc)
{
	char		*dest;
	t_vector2D	quote;
	t_vector2D	last_q;
	t_vector2D	it;

	it = (t_vector2D){0, 0};
	quote = (t_vector2D){0, 0};
	last_q = (t_vector2D){0, 0};
	dest = ft_malloc(sizeof(char) * (n + 1), &alloc);
	if (!dest)
		return (NULL);
	while (it.x < (int)n - 1 && src[it.x] != '\0')
	{
		dest = ft_lol((char *[2]){(char *)src, dest}, &quote, &last_q, &it);
		it.x++;
	}
	dest[it.y] = '\0';
	return (dest);
}

int	ft_body(char *s, t_vector2D *quoted, t_vector4D *it, char c)
{
	if (s[it->x + it->y] == '"' && !is_backed((char *)s, it->x + it->y - 1)
		&& !quoted->y)
		quoted->x = (quoted->x + 1) % 2;
	if (s[it->x + it->y] == '\'' && !quoted->x)
		quoted->y = (quoted->y + 1) % 2;
	if (s[it->x + it->y] == c && (!quoted->y && !quoted->x))
		return (0);
	it->y++;
	return (1);
}

static char	**ft_split_body_quote(char const *s, char c,
char **split, t_alloc *alloc)
{
	t_vector4D	it;
	t_vector2D	quoted;

	it = (t_vector4D){0, 0, 0, 0};
	quoted = (t_vector2D){0, 0};
	while (s[it.x])
	{
		while (s[it.x + it.y])
			if (!ft_body((char *)s, &quoted, &it, c))
				break ;
		if (it.y != 0)
		{
			if (!ft_body_2(&it, split, s, alloc))
				return (NULL);
		}
		it.x++;
	}
	split[it.z] = 0;
	return (split);
}

char	**ft_split_quote(char const *s, char c, t_alloc *alloc)
{
	char	**split;

	if (s == NULL)
		return (NULL);
	split = ft_malloc(sizeof(char *) * (count_words_quote(s, c) + 1), &alloc);
	if (!split)
		return (NULL);
	return (ft_split_body_quote(s, c, split, alloc));
}
