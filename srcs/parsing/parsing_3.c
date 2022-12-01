/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:01:35 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/01 16:04:09 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

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
			if (!split[k++])
				ft_black_hole(1);
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
	if (!split)
		return (NULL);
	return (ft_split_body(s, c, split));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (ft_black_hole(139), NULL);
	while (s1 && *s1)
	{
		str[i++] = *s1;
		s1++;
	}
	while (s2 && *s2)
	{
		str[i++] = *s2;
		s2++;
	}
	str[i] = 0;
	return (str);
}

char	*read_file(int fd)
{
	int		read_val;
	char	*str;
	char	*tmp;
	char	buff[1085];

	str = NULL;
	read_val = 1;
	while (read_val)
	{
		read_val = read(fd, buff, 1084);
		buff[read_val] = 0;
		tmp = str;
		str = ft_strjoin(tmp, buff);
	}
	return (str);
}

t_vector2D	get_pos(char **map, char c)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
				return ((t_vector2D){j, i});
			j++;
		}
		i++;
	}
	return ((t_vector2D){-1, -1});
}
