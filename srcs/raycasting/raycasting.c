/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:55:08 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/29 15:33:40 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	init_ray(void)
{
	t_vector2D	pos;

	pos = (t_vector2D){(_player()->x + 0.5), (_player()->y + 0.5)};
	_ray()->draw_end = 0;
	_ray()->draw_start = 0;
	_ray()->cam.x = 2 * _ray()->x / (double)WIN_W - 1;
	_ray()->dir.x = _player()->dx + _ray()->plane.x * _ray()->cam.x;
	_ray()->dir.y = _player()->dy + _ray()->plane.y * _ray()->cam.x;
	_ray()->map = pos;
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

static void	check(void)
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
	if (_ray()->map.y < _var()->map_height && _ray()->map.y >= 0
		&& _ray()->map.x < (int)ft_strlen(_var()->map[_ray()->map.y])
		&& _ray()->map.x >= 0
		&& _var()->map[_ray()->map.y][_ray()->map.x] == '1')
		_ray()->hit = 1;
}

void	dda(void)
{
	int	max;

	max = 0;
	while (!_ray()->hit)
	{
		if (max > 5000)
		{
			_player()->y -= 0.3;
			return ;
		}
		check();
		max++;
	}
}
