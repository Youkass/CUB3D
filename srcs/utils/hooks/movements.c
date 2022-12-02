/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:05:48 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/01 18:09:40 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

int	ft_down_head(void)
{
	int	norm;

	_player()->pitch -= 200 * _player()->move_speed;
	norm = normalise_between2f(posf(-1000, 1000),
			posf(-1, 1), _player()->pitch);
	if (_player()->pitch < -400)
		_player()->pitch = -400;
	_player()->norm_pitch = norm;
	return (0);
}

int	ft_forward(void)
{
	if (!check_neighbor(1))
	{
		_player()->y += (_player()->dy * _player()->move_speed);
		_player()->x += (_player()->dx * _player()->move_speed);
		_player()->is_walking = 1;
	}
	return (0);
}

int	ft_back(void)
{
	if (!check_neighbor(0))
	{
		_player()->y -= (_player()->dy * _player()->move_speed);
		_player()->x -= (_player()->dx * _player()->move_speed);
		_player()->is_walking = 1;
	}
	return (0);
}

int	ft_strafe_left(void)
{
	t_vector2F	dir;

	if (!check_neighbor(2))
	{
		dir = get_90_angle(-1);
		_player()->y += (dir.y * _player()->move_speed);
		_player()->x += (dir.x * _player()->move_speed);
		_player()->is_walking = 1;
	}
	return (0);
}

int	ft_strafe_right(void)
{
	t_vector2F	dir;

	if (!check_neighbor(3))
	{
		dir = get_90_angle(1);
		_player()->y += (dir.y * _player()->move_speed);
		_player()->x += (dir.x * _player()->move_speed);
		_player()->is_walking = 1;
	}
	return (0);
}
