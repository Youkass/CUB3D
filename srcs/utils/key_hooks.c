/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:55:05 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/05 17:30:28 by denissereno      ###   ########.fr       */
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
	//detect_neighbors();
	if (_var()->key.a)
		ft_left();
	if (_var()->key.w)
		ft_forward();
	if (_var()->key.s)
		ft_back();
	if (_var()->key.esc)
		ft_escape();
	if (_var()->key.d)
		ft_right();
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

int	ft_forward(void)
{
	if (!check_neighbor(1))
	{
		_player()->y += (_player()->dy * _player()->move_speed);
		_player()->x += (_player()->dx * _player()->move_speed);
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
	}
	return (0);
}

int	ft_right(void)
{
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
	return (0);
}

int	ft_escape(void)
{
	exit(1);
}
