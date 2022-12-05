/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:09:31 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/05 19:05:17 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	set_position(char c, t_vector2D it)
{
	if (c == 'N')
		set_pos(it, (t_vector2F){0.01, -1}, (t_vector2F){0.66, 0});
	else if (c == 'S')
		set_pos(it, (t_vector2F){0.01, 1}, (t_vector2F){-0.66, 0});
	else if (c == 'W')
		set_pos(it, (t_vector2F){-1, 0.01}, (t_vector2F){0, -0.66});
	else
		set_pos(it, (t_vector2F){1, 0.01}, (t_vector2F){0, 0.66});
}

static void	check(char c, t_vector2D it, char **map, t_vector2D pt)
{
	if (c == '0' || is_player(c))
	{
		if (!is_char_in_range(it, map))
		{
			printf("Error\nMap is not closed");
			ft_black_hole(0);
		}
		if (is_player(c))
			set_position(c, pt);
	}
	else if (c != '1' && c != ' ')
	{
		printf("Error\n%c: Unrecognized token\n", c);
		ft_black_hole(0);
	}
}

void	body_map(t_vector2D *pt, t_vector2D *it, char **map, int *longest)
{
	if (pt->y > 1024)
	{
		printf("Error\n%d size is to big, max 1024\n", pt->y);
		ft_black_hole(0);
	}
	it->x = 0;
	pt->x = 0;
	while (map[it->y][it->x])
	{
		check(map[it->y][it->x], *it, map, *pt);
		pt->x += 1;
		it->x += 1;
	}
	if (pt->x > *longest)
	{
		*longest = pt->x;
		if (*longest > 1024)
		{
			printf("Error\n%d size is to big, max 1024\n", *longest);
			ft_black_hole(0);
		}
	}
}

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
		ft_strcpy(_var()->map[pt.y], map[it.y]);
		pt.y++;
		it.y++;
	}
	_var()->map_width = longest;
	_var()->map_height = pt.y;
	_var()->map[pt.y][0] = 0;
	return (1);
}

void	error_dir(char *new, int index, int *nb, char *str)
{
	if (!_var()->dir[index].img)
	{
		printf("Error\n[%s]: does not valid\n", new);
		ft_black_hole(1);
	}
	if (*nb > 1)
	{
		printf("Error\n[%c%c]: Already defined\n", str[0], str[1]);
		ft_black_hole(1);
	}
}
