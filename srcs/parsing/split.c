/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:10:11 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/05 14:56:12 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

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

static char	*ft_strncpy_split(char const *src, size_t n)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = ft_malloc(sizeof(char) * n);
	while (i < n - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	*free_tab(char **tab, int k)
{
	while (k >= 0)
	{
		free(tab[k]);
		tab[k] = NULL;
		k--;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}

static char	**ft_split_body(char const *s, char c, char **split)
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
			split[k] = ft_strncpy_split(s + i, j + 1);
			i += j - 1;
			j = 0;
		}
		i++;
	}
	split[k] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (s == NULL)
		return (NULL);
	split = ft_malloc(sizeof(char *) * (count_words(s, c) + 1));
	return (ft_split_body(s, c, split));
}
