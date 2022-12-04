/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:10:14 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 16:51:31 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/*
===============================================================================
With the two next function we will transform our map parsed in char** to a 
cartesian plan by making a copy in t_obj.

reminder of our t_obj struct composition : 

typedef struct	s_obj
{
	int		id;
	int		x;
	int		y;
	char	c;
}	t_obj;
===============================================================================
*/
t_obj	*ft_copy_map_line(char *line, int index)
{
	int			i;
	t_vector2D	tmp;
	t_obj		*new_line;

	i = 1;
	new_line = ft_malloc(sizeof(t_obj) * _var()->map_width);
	if (!new_line)
		return (NULL);
	new_line[0].c = line[0];
	new_line[0].x = 0;
	new_line[0].y = _var()->scale * index;
	while (line[i])
	{
		tmp = pos(i, index);
		if (line[i] == 'X')
			_team()[TEAM_RED]->team_spawn = tmp;
		else if (line[i] == 'Y')
			_team()[TEAM_BLUE]->team_spawn = tmp;
		new_line[i].c = line[i];
		new_line[i].x = new_line[i - 1].x + _var()->scale;
		new_line[i].y = _var()->scale * index;
		++i;
	}
	return (new_line);
}

int	ft_malloc_map(void)
{
	int		j;
	t_obj	*line;

	j = 0;
	_var()->coord_map = ft_malloc(sizeof(t_obj *) * _var()->map_height);
	if (!_var()->coord_map)
		return (1);
	while (j < _var()->map_height)
	{
		line = ft_copy_map_line(_var()->map[j], j);
		_var()->coord_map[j] = line;
		if (!_var()->coord_map[j])
			return (1);
		++j;
	}
	ft_give_id();
	return (0);
}

/*
===============================================================================
The two following functions will draw square for the Wall obj and Floor obj
===============================================================================
*/
void	ft_draw_wall(t_vector2D pos)
{
	t_int	var;

	var.i = 0;
	while (var.i < _var()->scale)
	{
		var.j = 0;
		while (var.j < _var()->scale)
		{
			if (var.j == 0 || var.j == _var()->scale - 1 || var.i == 0
				|| var.i == _var()->scale - 1)
				ft_put_pixel_color(_img(), (char [4]){200, 142, 103, 100},
					(pos.x + 1) * _var()->scale + var.i, (pos.y + 1)
					* _var()->scale + var.j);
			var.j++;
		}
		var.i++;
	}
}

void	ft_draw_floor(t_vector2D pos)
{
	t_int	var;

	var.i = 0;
	while (var.i < _var()->scale)
	{
		var.j = 0;
		while (var.j < _var()->scale)
		{
			ft_put_pixel_color(_img(), (char [4]){255, 255, 255, 0},
				(int)(pos.x + 1) *_var()->scale + var.i, (int)(pos.y + 1)
				*_var()->scale + var.j);
			if (var.j == 0 || var.j == _var()->scale - 1 || var.i == 0
				|| var.i == _var()->scale - 1)
				ft_put_pixel_color(_img(), (char [4]){0, 0, 0, 0},
					(int)(pos.x + 1) *_var()->scale + var.i,
					(int)(pos.y + 1) *_var()->scale + var.j);
			var.j++;
		}
		var.i++;
	}
}

/*
===============================================================================
This is our main drawing function, we'll check every objects in the cartesian 
plan and draw it if needed it
===============================================================================
*/

void	drawcircle(int xp, int yp, float radius, int color)
{
	double	angle;
	double	i;
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (radius > 0)
	{
		i = 0;
		while (i < 360.0)
		{
			angle = i * PI / 180;
			x = (int)(radius * cos(angle));
			y = (int)(radius * sin(angle));
			ft_pixel_put(x + xp, y + yp, color);
			i += 0.1;
		}
		radius -= 0.1;
	}
}
