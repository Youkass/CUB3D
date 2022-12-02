/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:06:30 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/01 18:07:27 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

void	crouch(int mode)
{
	if (mode)
	{
		_player()->z = -100;
		_player()->is_crouching = 1;
	}
	else
	{
		_player()->z = 0;
		_player()->is_crouching = 0;
	}	
}

int	ft_up_head(void)
{
	int	norm;

	_player()->pitch += 200 * _player()->move_speed;
	norm = normalise_between2f(posf(-1000, 1000),
			posf(-1, 1), _player()->pitch);
	if (_player()->pitch > 400)
		_player()->pitch = 400;
	_player()->norm_pitch = norm;
	return (0);
}

int	ft_right(void)
{
	double	dist;

	_player()->old_dx = _player()->dx;
	_player()->dx = _player()->dx * cos(_player()->rot_speed)
	- _player()->dy * sin(_player()->rot_speed);
	_player()->dy = _player()->old_dx * sin(_player()->rot_speed)
	+ _player()->dy * cos(_player()->rot_speed);
	_player()->old_plane.x = _player()->plane.x;
	_player()->plane.x = _player()->plane.x * cos(_player()->rot_speed)
	- _player()->plane.y * sin(_player()->rot_speed);
	_player()->plane.y = _player()->old_plane.x * sin(_player()->rot_speed)
	+ _player()->plane.y * cos(_player()->rot_speed);
	dist = hypot(_player()->dx, _player()->dy);
	if (_player()->dy <= 0)
		_player()->angle = acos(_player()->dx / dist) * 180 / M_PI;
	else
		_player()->angle = 360 - acos(_player()->dx / dist) * 180 / M_PI;
	return (0);
}

int	ft_left(void)
{
	double	dist;

	_player()->old_dx = _player()->dx;
	_player()->dx = _player()->dx * cos(-_player()->rot_speed)
	- _player()->dy * sin(-_player()->rot_speed);
	_player()->dy = _player()->old_dx * sin(-_player()->rot_speed)
	+ _player()->dy * cos(-_player()->rot_speed);
	_player()->old_plane.x = _player()->plane.x;
	_player()->plane.x = _player()->plane.x * cos(-_player()->rot_speed)
	- _player()->plane.y * sin(-_player()->rot_speed);
	_player()->plane.y = _player()->old_plane.x * sin(-_player()->rot_speed)
	+ _player()->plane.y * cos(-_player()->rot_speed);
	dist = hypot(_player()->dx, _player()->dy);
	if (_player()->dy <= 0)
		_player()->angle = acos(_player()->dx / dist) * 180 / M_PI;
	else
		_player()->angle = 360 - acos(_player()->dx / dist) * 180 / M_PI;
	return (0);
}

void	movements(void)
{
	if (_var()->key[a])
		ft_strafe_left();
	if (_var()->key[w])
		ft_forward();
	if (_var()->key[s])
		ft_back();
	if (_var()->key[d])
		ft_strafe_right();
	if (_var()->key[left])
		ft_left();
	if (_var()->key[right])
		ft_right();
	if (_var()->key[up])
		ft_up_head();
	if (_var()->key[down])
		ft_down_head();
}
