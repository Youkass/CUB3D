/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:06:54 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/05 18:07:23 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub.h"

int	ft_expose(void *data)
{
	int			*mode;
	t_xvar		*var;
	t_win_list	*win;

	mode = (int *)data;
	if (*mode == GAME)
	{
		var = (t_xvar *)_mlx()->mlx;
		win = (t_win_list *)_mlx()->mlx_win;
		XFixesHideCursor(var->display, win->window);
		mlx_mouse_move(_mlx()->mlx, _mlx()->mlx_win, WIN_W / 2, WIN_H / 2);
	}
	return (0);
}

int	ft_rotate(double rot_speed)
{
	double	dist;

	_player()->old_dx = _player()->dx;
	_player()->dx = _player()->dx * cos(rot_speed)
	- _player()->dy * sin(rot_speed);
	_player()->dy = _player()->old_dx * sin(rot_speed)
	+ _player()->dy * cos(rot_speed);
	_player()->old_plane.x = _player()->plane.x;
	_player()->plane.x = _player()->plane.x * cos(rot_speed)
	- _player()->plane.y * sin(rot_speed);
	_player()->plane.y = _player()->old_plane.x * sin(rot_speed)
	+ _player()->plane.y * cos(rot_speed);
	dist = hypot(_player()->dx, _player()->dy);
	if (_player()->dy <= 0)
		_player()->angle = acos(_player()->dx / dist) * 180 / M_PI;
	else
		_player()->angle = 360 - acos(_player()->dx / dist) * 180 / M_PI;
	return (0);
}

int	mouse_rotate(void)
{
	t_vector2D	pos;
	t_vector2D	delta;
	t_vector2F	vec;
	t_vector2F	vec2;
	t_obj		*player;

	vec.x = -1000;
	vec.y = 1000;
	vec2.x = -1;
	vec2.y = 1;
	player = _player();
	pos = (t_vector2D){0, 0};
	mlx_mouse_get_pos(_mlx()->mlx, _mlx()->mlx_win, &pos.x, &pos.y);
	delta.x = pos.x - WIN_W / 2;
	delta.y = (pos.y - WIN_H / 2) * 25;
	ft_rotate(delta.x * _var()->frame_time * SENSIBILITY);
	player->pitch -= delta.y * player->move_speed;
	if (player->pitch > 500)
		player->pitch = 500;
	player->norm_pitch = normalise_between2f(vec, vec2, player->pitch);
	mlx_mouse_move(_mlx()->mlx, _mlx()->mlx_win, WIN_W / 2, WIN_H / 2);
	return (0);
}

int	ft_mouse_release(int keycode)
{
	if (keycode == 1)
		_var()->key[mouse] = 0;
	return (0);
}
