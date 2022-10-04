/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:55:08 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/03 18:54:05 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	init_ray(void)
{
	_ray()->draw_end = 0;
	_ray()->draw_start = 0;
	_ray()->cam.x = 2 * (_ray()->x / (double)WIN_H - 0.8);
	_ray()->dir.x =  _player()->dx + (_ray()->plane.x * _ray()->cam.x);
	_ray()->dir.y =  _player()->dy + (_ray()->plane.y * _ray()->cam.x);
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

/*
This calcultate the step size of x and y movement it's always between -1 and 1
beacause we are in a normalised tile world {pos player x = 1.5 mean that we
are in 1x tile of the map}.

The side_dist is the distance between the current pos to the next X side. So we
calculate the offset of the player onto his tile {_player{)->x + 0.5}} - _ray{}->map.x}.
Map.x is the current tile of player {example : 4} and {player{}.x +0.5 }is the actual
real position in this tile {example : 4.57}. So the offset on x axis is :
4.57 - 4 = 0.57.

The delta X value is normalize between 0 and 1 because of the direction of the 
X ray. If its totally straight it will be 1 or -1 because we have a step of 1 to
acces of 1 side to the other side of the cell. But if the ray_dir is not straight
we dont travel 1 by 1 to each side of x cell because of the inclinaison of
the camera. So we calculate the delta by : fabs{1 / _ray{}->dir.x} that give
us the % between 0 and 1 of the direction of the camera and we know the step
to access to another side of X.

And now we multiply the last result by delta so now side_dist.x = to the next
side of the cell that we are in. 

And its the same for y axis.
*/

void	init_dda(void)
{
	_ray()->hit = 0;
	if (_ray()->dir.x < 0)
	{
		_ray()->step.x = -1;
		_ray()->side_dist.x = (((_player()->x + 0.5)) - _ray()->map.x)
		* _ray()->delta.x;

	}
	else
	{
		_ray()->step.x = 1;
		_ray()->side_dist.x = (_ray()->map.x + 1 - ((_player()->x + 0.5)))
		* _ray()->delta.x;
	}
	if (_ray()->dir.y < 0)
	{
		_ray()->step.y = -1;
		_ray()->side_dist.y = ((_player()->y + 0.5) - _ray()->map.y)
		* _ray()->delta.y;
	}
	else
	{
		_ray()->step.y = 1;
		_ray()->side_dist.y = (_ray()->map.y + 1 - (_player()->y + 0.5))
		* _ray()->delta.y;
	}
}

/*
Now we have to raycasting until we touch a map obstacle. So while its not
touched we check if side_dist.x < side_dist.y or superior.

Check dda.png in the root folder.

Like in the drawing we have a red line that show the ray. The blue line is the
first offset to start at x side and the orange if for the y side. This is what we calculate
on _ray{}->side_dist.
So we start after that. The green and yello line is one unit of x and y and the
green dots are the X side intersection with the ray and yellow is for the y one.

So we check at the second green dot. Here side_dist->x will be equal to the first 
green dot to this dot here and side_dist-> y will be equal to the first yellow 
dot to the next one. So side_dist->y is superior than side_dist->x so we
know that the next cell we will check is at x+ 1. When we will encounter
the next yellow dot, side_dist->y will be inferior to side_dist->x because the next
green dot is after. So this time we will go cell y + 1.

So when we encounter a '1' we stop the dda and we have the coordinate of the
ray finishing.
*/

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
			_ray()->side_dist.y += _ray()->delta.y;
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
	_ray()->y = _ray()->draw_start;
	while(_ray()->y < _ray()->draw_end)
	{
		_ray()->tex_step = _ray()->y * _var()->menu->wall.line_length - WIN_H
		* _var()->menu->wall.line_length / 2 + _ray()->line_h * _var()->menu->wall.line_length / 2;
		_ray()->tex.y = ((_ray()->tex_step * _var()->menu->wall.height) / _ray()->line_h)
			/ _var()->menu->wall.line_length;
		_ray()->color = (int)_var()->menu->wall.addr[(_ray()->tex.y * _var()->menu->wall.line_length)  + (_ray()->tex.x * 4)];
		if(_ray()->side == 1)
			_ray()->color = (_ray()->color >> 1) & 8355711;
		ft_pixel_put((float)_ray()->x, (float)_ray()->y, _ray()->color);
		_ray()->y++;
	}
}

/*
-Algorithm to draw raycasting.
*/

void	draw_rays(void)
{
	int max;
	int	min;

	max = WIN_H;
	min = 0;
	_ray()->x = 0;
	while (_ray()->x < WIN_W)
	{
		init_ray();
		init_dda();
		dda();
		if (_ray()->hit == 0)
			continue ;
		compute_drawing_data();
		if (_ray()->draw_start < max)
			max = _ray()->draw_start;
		if (_ray()->draw_end > min)
			min = _ray()->draw_end;
		draw_wall();
		_ray()->x++;
	}
	if (_ray()->max_y >= 0)
		_ray()->max_y = max;
	if (_ray()->min_y >= 0)
		_ray()->min_y = min;
	// plot_line((t_vector2D){0, _ray()->max_y}, (t_vector2D){WIN_W, _ray()->max_y}, 0xcc1111);
	// plot_line((t_vector2D){0, _ray()->min_y}, (t_vector2D){WIN_W, _ray()->min_y}, 0xcc1111);
}

/*
Algo dont draw sky for nothing.

We take the highest y pixel write by the raycasting algorithm and to draw the next
sky draw sky from the y stocked to the bottom.                                                                                                                                                                        
*/