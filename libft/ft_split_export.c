/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:54:55 by alukongo          #+#    #+#             */
/*   Updated: 2022/09/12 13:13:54 by alukongo         ###   ########.fr       */
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

static char	*ft_strncpy_split(char const *src, size_t n, t_alloc *alloc)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = ft_malloc(sizeof(char) * n, &alloc);
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

static char	**ft_split_body(char const *s, char c, char **split, t_alloc *alloc)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (s[i + j] && s[i + j] != c)
		j++;
	if (s[i])
	{
		if (j != 0)
		{
			split[0] = ft_strncpy_split(s + i, j + 1, alloc);
			split[1] = ft_strncpy_split(s + j + 1, ft_strlen(s), alloc);
			if (!split[1] && !split[0])
				return (NULL);
		}
		i++;
	}
	split[2] = 0;
	return (split);
}

char	**ft_split_export(char const *s, char c, t_alloc *alloc)
{
	char	**split;

	if (s == NULL)
		return (NULL);
	split = ft_malloc(sizeof(char *) * (count_words(s, c) + 1), &alloc);
	if (!split)
		return (NULL);
	return (ft_split_body(s, c, split, alloc));
}
