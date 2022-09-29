/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:26:11 by yobougre          #+#    #+#             */
/*   Updated: 2022/09/29 22:30:50 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	ft_find_wall_scale(void)
{
	if (WIN_W > WIN_H)
		_img()->scale = (size_t)WIN_W / (ft_strlen(_img()->map[0]));
	else
		_img()->scale = (size_t)WIN_H / (ft_strlen(_img()->map[0]));
	//_img()->scale++;
}

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

void	ft_malloc_map(void)
{
	int	i;

	i = 0;
	ft_find_wall_scale();
	_img()->coord_map = malloc(sizeof(t_obj *) * _img()->map_width);
	if (!_img()->coord_map)
		return ; //TODO call garbage collector
	while (_img()->map[i])
	{
		_img()->coord_map[i] = ft_copy_map_line(_img()->map[i], i);
		if (!_img()->coord_map[i])
			return ; //TODO call garbage collector
		++i;
	}
	ft_give_id();
}

void	ft_draw_wall(t_obj wall)
{
	t_int	var;

	var.i = 0;
	while (var.i < _img()->scale) 
	{
		var.j = 0;
		while (var.j < _img()->scale)
		{
			ft_pixel_put(wall.x + var.i, wall.y + var.j, 0x0000FF00);
			if (var.j == 0 || var.j == _img()->scale - 1 || var.i == 0 ||
			var.i == _img()->scale - 1)
				ft_pixel_put(wall.x + var.i, wall.y + var.j, 0x00000000);
			var.j++;
		}
		var.i++;
	}
}

void	ft_draw_floor(t_obj wall)
{
	t_int	var;

	var.i = 0;
	while (var.i < _img()->scale) 
	{
		var.j = 0;
		while (var.j < _img()->scale)
		{
			ft_pixel_put(wall.x + var.i, wall.y + var.j, 0xFFFFFF);
			if (var.j == 0 || var.j == _img()->scale - 1 || var.i == 0 ||
			var.i == _img()->scale - 1)
				ft_pixel_put(wall.x + var.i, wall.y + var.j, 0x00000000);
			var.j++;
		}
		var.i++;
	}
}

void	ft_draw_map(void)
{
	t_int		var;
	t_vector2D	p_pos;

	var.i = 0;
	ft_malloc_map();
	while (var.i < _img()->map_height)
	{
		var.j = 0;
		while (var.j < _img()->map_width)
		{
			if (_img()->coord_map[var.i][var.j].id == WALL)
				ft_draw_wall(_img()->coord_map[var.i][var.j]);
			if (_img()->coord_map[var.i][var.j].id == MAP)
				ft_draw_floor(_img()->coord_map[var.i][var.j]);
			if (_img()->coord_map[var.i][var.j].id == PLAYER)
				p_pos = (t_vector2D){var.j, var.i};
			var.j++;
		}
		var.i++;
	}
	ft_draw_floor(_img()->coord_map[p_pos.y][p_pos.x]);
	ft_draw_player(_img()->coord_map[p_pos.y][p_pos.x]);
	draw_rays();
	mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win, _img()->img, 0, 0);
}
