/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:30:32 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/05 14:53:42 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
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
		if (read_val < 0)
			ft_black_hole(5);
		buff[read_val] = 0;
		tmp = str;
		str = ft_strjoin(tmp, buff);
	}
	return (str);
}

int	is_char_in_range(t_vector2D pos, char **map)
{
	t_vector2D			it;
	int					ok;
	static t_vector2D	add[4]
		= (t_vector2D [4]){{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	int					check;

	it = pos;
	check = -1;
	ok = 0;
	while (++check < 4)
	{
		while (pos.x >= 0 && pos.y >= 0 && map[pos.y][pos.x]
			&& map[pos.y][pos.x] != ' ')
		{
			if (map[pos.y][pos.x] == '1')
			{
				ok++;
				break ;
			}
			pos.x += add[check].x;
			pos.y += add[check].y;
		}
		pos = it;
	}
	return (ok == 4);
}

int	is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W' || c == 'P')
		return (1);
	return (0);
}
