/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:55:05 by yobougre          #+#    #+#             */
/*   Updated: 2022/12/04 20:49:42 by dasereno         ###   ########.fr       */
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
	if (_var()->key.a)
		ft_strafe_left();
	if (_var()->key.w)
		ft_forward();
	if (_var()->key.s)
		ft_back();
	if (_var()->key.esc)
		ft_escape();
	if (_var()->key.d)
		ft_strafe_right();
	if (_var()->key.left)
		ft_left();
	if (_var()->key.right)
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
	tab[2].ft_hook_key = &ft_strafe_left;
	tab[3].id = D;
	tab[3].ft_hook_key = &ft_strafe_right;
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

int	ft_right(void)
{
	double		at;

	at = atan2(_player()->dy, _player()->dx);
	_player()->old_dx = _player()->dx;
	_player()->dx = _player()->dx * cos(_player()->rot_speed)
	- _player()->dy * sin(_player()->rot_speed);
	_player()->dy = _player()->old_dx * sin(_player()->rot_speed)
	+ _player()->dy * cos(_player()->rot_speed);
	_ray()->old_plane.x = _ray()->plane.x;
	_ray()->plane.x = _ray()->plane.x * cos(_player()->rot_speed)
	- _ray()->plane.y * sin(_player()->rot_speed);
	_ray()->plane.y = _ray()->old_plane.x * sin(_player()->rot_speed)
	+ _ray()->plane.y * cos(_player()->rot_speed);
	_player()->angle = at;
	return (0);
}

int	ft_left(void)
{
	double		at;

	at = atan2(_player()->dy, _player()->dx);
	_player()->old_dx = _player()->dx;
	_player()->dx = _player()->dx * cos(-_player()->rot_speed) - _player()->dy
	* sin(-_player()->rot_speed);
	_player()->dy = _player()->old_dx * sin(-_player()->rot_speed)
	+ _player()->dy * cos(-_player()->rot_speed);
	_ray()->old_plane.x = _ray()->plane.x;
	_ray()->plane.x = _ray()->plane.x * cos(-_player()->rot_speed)
	- _ray()->plane.y * sin(-_player()->rot_speed);
	_ray()->plane.y = _ray()->old_plane.x * sin(-_player()->rot_speed)
	+ _ray()->plane.y * cos(-_player()->rot_speed);
	_player()->angle = at;
	return (0);
}

int	ft_escape(void)
{
	ft_black_hole(1);
	return (0);
}
