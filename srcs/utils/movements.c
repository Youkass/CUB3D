/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:52:53 by dasereno          #+#    #+#             */
/*   Updated: 2022/11/29 16:57:34 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	ft_forward(void)
{
	t_vector2F	tmp;

	tmp.y = _player()->y + (_player()->dy * (_player()->move_speed));
	tmp.x = _player()->x + (_player()->dx * (_player()->move_speed));
	if (_var()->map[(int)tmp.y][(int)tmp.x] != '1')
	{
		_player()->y += (_player()->dy * (_player()->move_speed));
		_player()->x += (_player()->dx * (_player()->move_speed));
	}
	else
	{
		_player()->y -= (_player()->dy * (_player()->move_speed));
		_player()->x -= (_player()->dx * (_player()->move_speed));
	}
	return (0);
}

int	ft_back(void)
{
	t_vector2F	tmp;

	tmp.y = _player()->y - (_player()->dy * (_player()->move_speed));
	tmp.x = _player()->x - (_player()->dx * (_player()->move_speed));
	if (_var()->map[(int)tmp.y][(int)tmp.x] != '1')
	{
		_player()->y -= (_player()->dy * (_player()->move_speed));
		_player()->x -= (_player()->dx * (_player()->move_speed));
	}
	else
	{
		_player()->y += (_player()->dy * (_player()->move_speed));
		_player()->x += (_player()->dx * (_player()->move_speed));
	}
	return (0);
}

int	ft_strafe_left(void)
{
	t_vector2F	dir;
	t_vector2F	tmp;

	dir = get_90_angle(-1);
	tmp.x = _player()->y + (dir.y * _player()->move_speed);
	tmp.y = _player()->x + (dir.x * _player()->move_speed);
	if (_var()->map[(int)tmp.x][(int)tmp.y] != '1')
	{
		_player()->y += (dir.y * _player()->move_speed);
		_player()->x += (dir.x * _player()->move_speed);
	}
	else
	{
		_player()->y -= (dir.y * _player()->move_speed);
		_player()->x -= (dir.x * _player()->move_speed);
	}
	return (0);
}

int	ft_strafe_right(void)
{
	t_vector2F	dir;
	t_vector2F	tmp;

	dir = get_90_angle(-1);
	tmp.x = _player()->y - (dir.y * _player()->move_speed);
	tmp.y = _player()->x - (dir.x * _player()->move_speed);
	if (_var()->map[(int)tmp.x][(int)tmp.y] != '1')
	{
		_player()->y -= (dir.y * _player()->move_speed);
		_player()->x -= (dir.x * _player()->move_speed);
	}
	else
	{
		_player()->y += (dir.y * _player()->move_speed);
		_player()->x += (dir.x * _player()->move_speed);
	}
	return (0);
}

t_vector2F	get_90_angle(int dir)
{
	double		deg;
	double		rad;
	t_vector2F	v;

	deg = rad_to_deg(atan2(_player()->dy, _player()->dx)) + (90 * dir);
	rad = deg_to_rad(deg);
	v.x = (cos(rad));
	v.y = (sin(rad));
	v.x += _player()->dx;
	v.y += _player()->dy;
	deg = (atan2(v.y - _player()->dy, v.x - _player()->dx));
	return ((t_vector2F){cos(deg), sin(deg)});
}
