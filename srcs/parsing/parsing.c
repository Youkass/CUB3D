/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 19:43:10 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/01 16:01:26 by dasereno         ###   ########.fr       */
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

int	check_map(char **map, int start)
{
	t_vector2D	it;
	t_vector2D	pt;
	int			longest;

	it = (t_vector2D){0, start};
	pt = (t_vector2D){0, 0};
	longest = 0;
	while (map[it.y])
	{
		body_map(&pt, &it, map, &longest);
		strcpy(_var()->map[pt.y], map[it.y]);
		pt.y++;
		it.y++;
	}
	_var()->map_width = longest;
	_var()->map_height = pt.y;
	_var()->map[pt.y][0] = 0;
	return (1);
}

int	get_longest_line(char **map)
{
	int	i;
	int	max;

	i = 0;
	max = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > (size_t)max)
			max = ft_strlen(map[i]);
		i++;
	}
	if (i > 1024)
		ft_black_hole(10);
	return (max);
}

char	*copy_line_and_add(char *str, int size)
{
	int		i;
	char	*new;

	i = 0;
	new = ft_malloc(sizeof(char) * (size + 1));
	while (str[i])
	{
		if (str[i] == ' ')
			new[i] = 'Z';
		else
			new[i] = str[i];
		i++;
	}
	while (i < size)
		new[i++] = 'Z';
	new[i] = 0;
	return (new);
}

char	**resize_map(char **map)
{
	int		max;
	int		i;
	char	**new;

	max = get_longest_line(map);
	if (max > 1024)
		ft_black_hole(10);
	new = ft_malloc(sizeof(char *) * 100);
	i = 0;
	while (map[i])
	{
		new[i] = copy_line_and_add(map[i], max);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	copy_map_static(void)
{
	int	i;
	int	j;

	i = 0;
	while (_var()->before_map[i])
	{
		j = 0;
		while (_var()->before_map[i][j])
		{
			_var()->map[i][j] = _var()->before_map[i][j];
			j++;
		}
		_var()->map[i][j] = 0;
		i++;
	}
}
