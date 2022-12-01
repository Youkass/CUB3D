/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:01:02 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/01 17:25:02 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

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
			if (is_wall(map[pos.y][pos.x]))
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

int	is_wall(char c)
{
	if ((c >= '1' && c <= '9') || c == 'A' || c == 'B')
		return (1);
	return (0);
}

int	is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W' || c == 'P')
		return (1);
	return (0);
}

static void	check(char c, t_vector2D it, char **map)
{
	if (c == '0' || is_player(c))
	{
		if (!is_char_in_range(it, map))
			ft_black_hole(19);
	}
	else if (!is_wall(c) && c != ' ')
		ft_black_hole(18);
}

void	body_map(t_vector2D *pt, t_vector2D *it, char **map, int *longest)
{
	if (pt->y > 1024)
		ft_black_hole(10);
	it->x = 0;
	pt->x = 0;
	while (map[it->y][it->x])
	{
		check(map[it->y][it->x], *it, map);
		pt->x += 1;
		it->x += 1;
	}
	if (pt->x > *longest)
	{
		*longest = pt->x;
		if (*longest > 1024)
			ft_black_hole(10);
	}
}
