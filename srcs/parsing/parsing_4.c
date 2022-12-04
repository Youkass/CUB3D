/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:02:03 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 18:17:38 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	count_words(char const *s, char c)
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

char	*ft_strncpy_split(char const *src, size_t n)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = ft_malloc(sizeof(char) * n);
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

int	is_wall(char c)
{
	if ((c >= '1' && c <= '9') || c == 'A' || c == 'B' || c == 'D')
		return (1);
	return (0);
}
