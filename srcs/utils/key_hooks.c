/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:55:05 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/21 21:32:51 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/*
===============================================================================
instead of making a condition branch for each case 
(and to stay in the 42 norm of coding)
we assign for each element of 'tab' who is an array of t_enum_key a keycode as
an ID, that will call the corresponding function
t_enum_key struct composition :

typedef struct s_enum_key
{
	int	id;
	int	(*ft_hook_key)(void);
}	t_enum_key;

===============================================================================
*/

void	key_hook(void)
{
	if (_var()->key.esc)
		ft_escape();
	if (_player()->is_dead)
		return ;
	if (_var()->key.a)
		ft_left();
	if (_var()->key.w)
		ft_forward();
	if (_var()->key.s)
		ft_back();
	if (_var()->key.d)
		ft_right();
	if (_var()->key.up)
		ft_up_head();
	if (_var()->key.down)
		ft_down_head();
	if (_var()->key.space)
	{
		if (_var()->mode == GAME)
		{
			_player()->can_shoot = 0;
			_player()->start_reload = get_clock(_var()->clock);
			shoot();
		}
		else if (_img()->is_host == SERVER) // menu lobby
		{
			int	neg;

			neg = -1;
			send(_img()->socket, &neg, sizeof(int), 0);
			send(_img()->socket, &_player()->id, sizeof(int), 0);
			recv(_img()->socket, &neg, sizeof(int), 0);
			send(_img()->socket, &_player()->id, sizeof(int), 0);
			_var()->mode = GAME;
			//_var()->mode = GAME;
		}
	}
}

int	ft_game_hook(int keycode)
{
	int			i;
	t_enum_key	tab[MAX_KEYS];

	i = 0;
	tab[0].id = W;
	tab[0].ft_hook_key = &ft_forward;
	tab[1].id = S;
	tab[1].ft_hook_key = &ft_back;
	tab[2].id = A;
	tab[2].ft_hook_key = &ft_left;
	tab[3].id = D;
	tab[3].ft_hook_key = &ft_right;
	tab[4].id = ESC;
	tab[4].ft_hook_key = &ft_escape;
	while (i < MAX_KEYS)
	{
		if (tab[i].id == keycode)
			return (tab[i].ft_hook_key());
		++i;
	}
	return (0);
}
/*
================================================================================
all the following functions are the function we assigned just above this comment
================================================================================
*/

int	ft_up_head(void)
{
	_player()->pitch += 200 * _player()->move_speed;
	if(_player()->pitch > 400)
		_player()->pitch = 400;
	return (0);
}

int	ft_down_head(void)
{
	_player()->pitch -= 200 * _player()->move_speed;
	if(_player()->pitch < -400)
		_player()->pitch = -400;
	return (0);
}

int	ft_jump(void)
{
	_player()->z = 200;
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

int	ft_is_wall(t_vector2D pos)
{
	if (pos.x >= 0 && pos.y >= 0 && pos.x < _img()->map_width
		&& pos.y < _img()->map_height && _img()->map[pos.y][pos.x] == '1')
		return (1);
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
	double dist = hypot(_player()->dx, _player()->dy);
	if (_player()->dy <= 0)
		_player()->angle = acos(_player()->dx / dist) * 180 / M_PI;
	else
		_player()->angle = 360 - acos(_player()->dx / dist) * 180 / M_PI;
	return (0);
}

int	ft_escape(void)
{
	exit(1);
	return (0);
}
