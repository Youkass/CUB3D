/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:26:11 by yobougre          #+#    #+#             */
/*   Updated: 2022/11/20 21:56:36 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/*
===============================================================================
The following function will give us the right size for the elements in the 2D 
map.
===============================================================================
*/

/*
===============================================================================
Here we're giving to each objects in the cartesian plan an ID 
===============================================================================
*/
void	ft_give_id(void)
{
	int	i;
	int	j;

	i = 0;
	while (i < _img()->map_height)
	{
		j = 0;
		while (j < _img()->map_width)
		{
			if (_img()->coord_map[i][j].c == 'Z')
				_img()->coord_map[i][j].id = VOID;
			if (_img()->coord_map[i][j].c == '1')
				_img()->coord_map[i][j].id = WALL;
			if (_img()->coord_map[i][j].c == '0')
				_img()->coord_map[i][j].id = MAP;
			if (_img()->coord_map[i][j].c == 'P')
				_img()->coord_map[i][j].id = PLAYER;
			++j;
		}
		++i;
	}
}

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

/*
===============================================================================
The two following functions will draw square for the Wall obj and Floor obj
===============================================================================
*/
void	ft_draw_wall(t_obj wall)
{
	t_int	var;

	var.i = 0;
	while (var.i < _img()->scale) 
	{
		var.j = 0;
		while (var.j < _img()->scale)
		{
			ft_pixel_put(wall.x + var.i + MINIMAP_OFFSET, wall.y + var.j, 0x0000FF00);
			if (var.j == 0 || var.j == _img()->scale - 1 || var.i == 0 ||
			var.i == _img()->scale - 1)
				ft_pixel_put(wall.x + var.i + MINIMAP_OFFSET, wall.y + var.j, 0x00000000);
			var.j++;
		}
		var.i++;
	}
}

void	ft_draw_floor(t_obj wall, t_vector2D pos)
{
	t_int	var;

	var.i = 0;
	while (var.i < _img()->scale) 
	{
		var.j = 0;
		while (var.j < _img()->scale)
		{
			if (is_neighbor(pos))
				ft_pixel_put(wall.x + var.i + MINIMAP_OFFSET, wall.y + var.j, 0x6b6b69);
			else
				ft_pixel_put(wall.x + var.i + MINIMAP_OFFSET, wall.y + var.j, 0xFFFFFF);
			if (var.j == 0 || var.j == _img()->scale - 1 || var.i == 0 ||
			var.i == _img()->scale - 1)
				ft_pixel_put(wall.x + var.i + MINIMAP_OFFSET, wall.y + var.j, 0x00000000);
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

void DrawCircle(int xp, int yp, float radius, int color)
{
	double	angle;
	double	i;
	int		x;
	int		y;

	i = 0.0;
	while (i < 360.0)
	{
		angle = i *  PI / 180;
		x = (int)(radius * cos(angle));
		y = (int)(radius * sin(angle));
		ft_pixel_put(x + xp, y + yp, color);
		i += 0.1;
	}
}

void	ft_put_pixel_color(t_data *a, unsigned char color[4], int x, int y)
{
	if (color[3] != 255)
	{
		a->addr[y * a->line_length + x * 4] = color[0];
		a->addr[(y * a->line_length + x * 4) + 1] = color[1];
		a->addr[(y * a->line_length + x * 4) + 2] = color[2];
		a->addr[(y * a->line_length + x * 4) + 3] = color[3];
	}
}

void	draw_void(void)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (y < WIN_H / 2 && x < WIN_W)
		{
			ft_put_pixel_color(_img(), _var()->colors[1],
				x, y);
			x++;
		}
		while (y < WIN_H && y > WIN_H / 2 && x < WIN_W)
		{
			ft_put_pixel_color(_img(), _var()->colors[0],
				x, y);
			x++;
		}
		y++;
	}
}
