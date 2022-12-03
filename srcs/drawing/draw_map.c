/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:26:11 by yobougre          #+#    #+#             */
/*   Updated: 2022/12/03 16:52:43 by yobougre         ###   ########.fr       */
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
	_var()->scale = 11;
	_var()->half_scale = _var()->scale / 2;
	_var()->half_scale_offset = _var()->half_scale + MINIMAP_OFFSET
	- _player()->x * _var()->scale - 350;
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
	while (i < _var()->map_height)
	{
		j = 0;
		while (j < _var()->map_width)
		{
			if (_var()->coord_map[i][j].c == 'Z')
				_var()->coord_map[i][j].id = VOID;
			if (_var()->coord_map[i][j].c == '1')
				_var()->coord_map[i][j].id = WALL;
			if (_var()->coord_map[i][j].c == '0')
				_var()->coord_map[i][j].id = MAP;
			if (_var()->coord_map[i][j].c == 'P')
				_var()->coord_map[i][j].id = PLAYER;
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
	new_line = ft_malloc(sizeof(t_obj) * _var()->map_width);
	if (!new_line)
		return (NULL);
	new_line[0].c = line[0];
	new_line[0].x = 0;
	new_line[0].y = _var()->scale * index;
	while (line[i])
	{
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
				ft_put_pixel_color(_img(), colo(200, 142, 103), (pos.x + 1)
					* _var()->scale + var.i, (pos.y + 1)
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

static void	ft_draw_first(void)
{
	int		i;
	t_obj	player;
	t_obj	my_player;

	i = 0;
	while (i < _var()->linked_players / 2)
	{
		player = _var()->o_player[_var()->red[i]];
		if (_player()->spectate && _player()->spec_id >= 0
			&& _player()->spec_id < _var()->linked_players)
			my_player = _var()->o_player[_player()->spec_id];
		else
			my_player = *_player();
		if (player.x >= my_player.x - 8 && player.x <= my_player.x + 8
			&& player.y >= my_player.y - 8 && player.y <= my_player.x + 8)
			drawcircle(ft_return_xp(&player, &my_player),
				ft_return_yp(&player, &my_player),
				ft_return_radius(&player), 0xD2042D);
		i++;
	}
}

static void	ft_draw_next(void)
{
	int		i;
	t_obj	player;
	t_obj	my_player;

	i = 0;
	while (i < _var()->linked_players / 2)
	{
		player = _var()->o_player[_var()->blue[i]];
		if (_player()->spectate && _player()->spec_id >= 0
			&& _player()->spec_id < _var()->linked_players)
			my_player = _var()->o_player[_player()->spec_id];
		else
			my_player = *_player();
		if (player.x >= my_player.x - 8 && player.x <= my_player.x + 8
			&& player.y >= my_player.y - 8 && player.y <= my_player.x + 8)
			drawcircle(ft_return_xp(&player, &my_player),
				ft_return_yp(&player, &my_player),
				ft_return_radius(&player), 0x005b96);
		i++;
	}
}

void	draw_player_map(void)
{
	if ((_var()->is_host == CLIENT || _var()->is_host == SERVER)
		&& _player()->team == TEAM_RED)
		ft_draw_first();
	else if ((_var()->is_host == CLIENT || _var()->is_host == SERVER)
		&& _player()->team == TEAM_BLUE)
		ft_draw_next();
	else
		drawcircle(ft_return_xp(_player(), _player()), ft_return_yp(_player(),
				_player()), ft_return_radius(_player()), 0xD2042D);
}

static void	ft_draw_map_next(t_int var, t_vector2D offset)
{
	if (is_wall(_var()->map[var.i][var.j]))
		ft_draw_wall(offset);
	if (_var()->map[var.i][var.j] == '0')
		ft_draw_floor(offset);
	if (is_player(_var()->map[var.i][var.j]))
		ft_draw_floor(offset);
}

void	ft_draw_map(void)
{
	t_int		var;
	t_vector2D	offset;

	var.i = _player()->y - MINIMAP_SIZE;
	offset = pos(0, 0);
	if (var.i < 0)
		var.i = 0;
	while (var.i < _var()->map_height && var.i < _player()->y + MINIMAP_SIZE)
	{
		var.j = _player()->x - MINIMAP_SIZE;
		if (var.j < 0)
			var.j = 0;
		offset.x = 0;
		while (var.j < _var()->map_width && var.j < _player()->x + MINIMAP_SIZE)
		{
			ft_draw_map_next(var, offset);
			var.j++;
			offset.x++;
		}
		offset.y++;
		var.i++;
	}
	draw_player_map();
	mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win, _img()->img, 0, 0);
}
