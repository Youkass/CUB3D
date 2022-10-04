/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:26:11 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/03 18:22:12 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/*
===============================================================================
The following function will give us the right size for the elements in the 2D 
map.
===============================================================================
*/
void	ft_find_wall_scale(void)
{
	_img()->scale = MINIMAP_SIZE / ft_strlen(_img()->map[0]);
	_img()->half_scale = _img()->scale / 2;
	_img()->half_scale_offset = _img()->half_scale + MINIMAP_OFFSET;
}

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
t_obj	*ft_copy_map_line(char *line, int index)
{
	int		i;
	t_obj	*new_line;

	i = 1;
	new_line = malloc(sizeof(t_obj) * _img()->map_width);
	if (!new_line)
		return (NULL);
	new_line[0].c = line[0];
	new_line[0].x = 0;
	new_line[0].y = _img()->scale * index;
	while (line[i])
	{
		new_line[i].c = line[i];
		new_line[i].x = new_line[i - 1].x + _img()->scale;
		new_line[i].y = _img()->scale * index;
		++i;
	}
	return (new_line);
}

int	ft_malloc_map(void)
{
	int	i;

	i = 0;
	ft_find_wall_scale();
	_img()->coord_map = malloc(sizeof(t_obj *) * _img()->map_width);
	if (!_img()->coord_map)
		return (1); //TODO call garbage collector
	while (_img()->map[i])
	{
		_img()->coord_map[i] = ft_copy_map_line(_img()->map[i], i);
		if (!_img()->coord_map[i])
			return (1); //TODO call garbage collector
		++i;
	}
	ft_give_id();
	return (0);
}

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


void	ft_draw_map(void)
{
	t_int		var;
	t_vector2D	p_pos;

	var.i = 0;
	draw_rays();
	while (var.i < _img()->map_height)
	{
		var.j = 0;
		while (var.j < _img()->map_width)
		{
			if (_img()->coord_map[var.i][var.j].id == WALL)
				ft_draw_wall(_img()->coord_map[var.i][var.j]);
			if (_img()->coord_map[var.i][var.j].id == MAP)
				ft_draw_floor(_img()->coord_map[var.i][var.j], (t_vector2D){var.j, var.i});
			if (_img()->coord_map[var.i][var.j].id == PLAYER)
			{
				p_pos = (t_vector2D){var.j, var.i};
				ft_draw_floor(_img()->coord_map[p_pos.y][p_pos.x], (t_vector2D){var.j, var.i});
			}
			var.j++;
		}
		var.i++;
	}
	DrawCircle(ft_return_xp(), ft_return_yp(), ft_return_radius(), 0xFFFF0000);
	plot_line(ft_first_vector(), ft_scnd_vector(), 0xcf34eb);
	mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win, _img()->img, 0, 0);
}
