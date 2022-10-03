/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:55:08 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/03 12:07:49 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	init_ray(void)
{
		_ray()->draw_end = 0;
		_ray()->draw_start = 0;
		_ray()->cam.x = 2 * _ray()->x / (double)WIN_H - 1;
		_ray()->dir.x =  _player()->dx + _ray()->plane.x * _ray()->cam.x;
		_ray()->dir.y =  _player()->dy + _ray()->plane.y * _ray()->cam.x;
		_ray()->map = (t_vector2D){(_player()->x + 0.5), (_player()->y + 0.5)};
		if (_ray()->dir.y == 0)
			_ray()->delta.x = 0;
		else if (_ray()->dir.x == 0)
			_ray()->delta.x = 1;
		else
			_ray()->delta.x = fabs(1 / _ray()->dir.x);
		if (_ray()->dir.x == 0)
			_ray()->delta.y = 0;
		else if (_ray()->dir.y == 0)
			_ray()->delta.y = 1;
		else
			_ray()->delta.y = fabs(1 / _ray()->dir.y);
}

void	compute_side_distance(void)
{
	_ray()->hit = 0;
	if (_ray()->dir.x < 0)
	{
		_ray()->step.x = -1;
		_ray()->side_dist.x = (((_player()->x + 0.5)) - _ray()->map.x) * _ray()->delta.x;
	}
	else
	{
		_ray()->step.x = 1;
		_ray()->side_dist.x = (_ray()->map.x + 1 - ((_player()->x + 0.5))) * _ray()->delta.x;
	}
	if (_ray()->dir.y < 0)
	{
		_ray()->step.y = -1;
		_ray()->side_dist.y = ((_player()->y + 0.5) - _ray()->map.y) * _ray()->delta.y;
	}
	else
	{
		_ray()->step.y = 1;
		_ray()->side_dist.y = (_ray()->map.y + 1 - (_player()->y + 0.5)) * _ray()->delta.y;
	}
}

void	dda(void)
{
	while (!_ray()->hit)
	{
		if (_ray()->side_dist.x < _ray()->side_dist.y)
		{
			_ray()->side_dist.x += _ray()->delta.x;
			_ray()->map.x += _ray()->step.x;
			_ray()->side = 0;
		}
		else
		{
			_ray()->side_dist.y+= _ray()->delta.y;
			_ray()->map.y += _ray()->step.y;
			_ray()->side = 1;
		}
		if (_ray()->map.y < _img()->map_height && _ray()->map.y >= 0 &&
			_ray()->map.x < _img()->map_width && _ray()->map.x >= 0
			&& _img()->map[_ray()->map.y][_ray()->map.x] == '1') // ! Possible crash si pas de mur ( rajouter condition pour break)
			_ray()->hit = 1;
	}
}

void	compute_drawing_data()
{

	if (_ray()->side == 0)
		_ray()->perp_wall_dist = (_ray()->side_dist.x - _ray()->delta.x);
	else
		_ray()->perp_wall_dist = (_ray()->side_dist.y - _ray()->delta.y);

	_ray()->line_h = (int)(WIN_H / _ray()->perp_wall_dist);
	_ray()->draw_start = -_ray()->line_h / 2 + WIN_H / 2;
	if (_ray()->draw_start < 0)
		_ray()->draw_start = 0;
	_ray()->draw_end = _ray()->line_h / 2 + WIN_H / 2;
	if (_ray()->draw_end > WIN_H)
		_ray()->draw_end = WIN_H - 1;
	if (_ray()->side == 0)
		_ray()->wall_x = (_player()->y + 0.5) + _ray()->perp_wall_dist * _ray()->dir.y;
	else
		_ray()->wall_x = (_player()->x + 0.5) + _ray()->perp_wall_dist * _ray()->dir.x;
	_ray()->wall_x -= floor(_ray()->wall_x);
}

void	draw_wall(void)
{
	_ray()->tex.x = (int){_ray()->wall_x * 64.0};
	if (_ray()->side == 0 && _ray()->dir.x > 0)
		_ray()->tex.x = 64 - _ray()->tex.x - 1;
	else if (_ray()->side == 1 && _ray()->dir.y < 0)
		_ray()->tex.x = 64 - _ray()->tex.x - 1;

	_ray()->tex_pos = (_ray()->draw_start - WIN_H / 2 + _ray()->line_h / 2);
	for(int y = _ray()->draw_start; y < _ray()->draw_end; y++)
	{
		_ray()->tex_step = y * _var()->menu->wall.line_length - WIN_H
			* _var()->menu->wall.line_length / 2 + _ray()->line_h * _var()->menu->wall.line_length / 2;
		_ray()->tex.y = ((_ray()->tex_step * _var()->menu->wall.height) / _ray()->line_h)
			/ _var()->menu->wall.line_length;
		_ray()->tex_pos += _ray()->tex_step;
		_ray()->color = (int)_var()->menu->wall.addr[(_ray()->tex.y * _var()->menu->wall.line_length)  + (_ray()->tex.x * 4)];
		if(_ray()->side == 1)
			_ray()->color = (_ray()->color >> 1) & 8355711;
		ft_pixel_put((float)_ray()->x, (float)y, _ray()->color);
	}
}

/*
-Algorithm to draw raycasting.
*/

void	draw_rays(void)
{
	_ray()->x = 0;

	while (_ray()->x <= WIN_W)
	{
		init_ray();
		compute_side_distance();
		dda();
		if (_ray()->hit == 0)
			continue;
		compute_drawing_data();
		draw_wall();
		_ray()->x++;
	}
}
