/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:47:05 by darian            #+#    #+#             */
/*   Updated: 2022/09/12 13:13:39 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	count_words(char const *s, char c)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
			w++;
		i++;
	}
	return (w);
}

static char	*ft_strncpy_split(char const *src, size_t n, t_alloc **alloc)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = ft_malloc(sizeof(char) * n, alloc);
	if (!dest)
		return (NULL);
	while (i < n - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	**ft_split_body(char const *s, char c,
char **split, t_alloc **alloc)
{
	int	j;
	int	k;
	int	i;

	i = 0;
	j = 0;
	k = 0;
	while (s[i])
	{
		while (s[i + j] && s[i + j] != c)
			j++;
		if (j != 0)
		{
			split[k] = ft_strncpy_split(s + i, j + 1, alloc);
			if (!split[k++])
				return (NULL);
			i += j - 1;
			j = 0;
		}
		i++;
	}
	split[k] = 0;
	return (split);
}

char	**ft_split(char const *s, char c, t_alloc **alloc)
{
	char	**split;

	if (s == NULL)
		return (NULL);
	split = ft_malloc(sizeof(char *) * (count_words(s, c) + 1), alloc);
	if (!split)
		return (NULL);
	return (ft_split_body(s, c, split, alloc));
}
