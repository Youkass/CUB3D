/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:55:05 by yobougre          #+#    #+#             */
/*   Updated: 2022/11/18 20:52:53 by dasereno         ###   ########.fr       */
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

void	crouch(int	mode)
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

void	key_hook(void)
{
	if (_var()->key[esc])
		ft_escape();
	if (_player()->is_dead || _var()->freeze || click_delay())
		return ;
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
	if (_var()->key[mouse])
	{
		if (_menu()->mode == INTRO)
			_menu()->mode = MENU_START;
		if (_var()->mode == GAME && _player()->can_shoot && _player()->shoot_n < MAX_BULLET
		&& _player()->ammo[_player()->weapon_id] > 0)
		{
			_player()->can_shoot = 0;
			_player()->is_shooting = 1;
			--_player()->ammo[_player()->weapon_id];
			_player()->start_reload = get_clock(_var()->clock);
			shoot();
		}
	}
	if (_player()->id == 0 &&_var()->key[maj] && _var()->mode == MENU)
	{
		printf("click\n");
		click();
		_var()->restart = 1;
	}
	if (_var()->key[one] && _var()->mode == GAME)
		_player()->weapon_id = 0;
	if (_var()->key[two] && _var()->mode == GAME)
		_player()->weapon_id = 1;
	if (_var()->key[three] && _var()->mode == GAME)
		_player()->weapon_id = 2;
	if (_var()->key[f] && _var()->mode == GAME)
		_player()->weapon_id = mod(_player()->weapon_id + 1, 3);
	if (_var()->key[space])
	{
		if (_menu()->mode == INTRO)
			_menu()->mode = MENU_START;
		if (_var()->is_host == SERVER && _menu()->mode == MENU_LOBBY && _var()
			->mode != GAME && _var()->nb_player == _var()->linked_players
			 && is_neutral()) // menu lobby
		{
			_player()->is_start = 1;
			printf("j'ai appuyé sur space\n");
		}
	}
	if (_var()->key[r])
	{
		if (_var()->mode == GAME && _player()->full_ammo[_player()->weapon_id] > 0 && _player()->ammo[_player()->weapon_id] < 15
		&& _player()->weapon_id != KNIFE)
		{
			int	needed;

			needed = abs(_player()->ammo[_player()->weapon_id] - 15);
			if (_player()->full_ammo[_player()->weapon_id] <= needed)
				needed = _player()->full_ammo[_player()->weapon_id];
			_player()->full_ammo[_player()->weapon_id] -= needed;
			_player()->ammo[_player()->weapon_id] += needed;
			_var()->reload_anim = 1;
			_var()->reloadanim_start = get_clock(_var()->clock);
		}
	}
	if (_var()->key[maj] && _var()->mode == GAME)
	{
		crouch(1);
		printf("crouch\n");
	}
	else if (!_var()->key[maj] && _var()->mode == GAME)
		crouch(0);
}

int	ft_game_hook(int keycode)
{
	int			i;
	t_enum_key	tab[MAX_KEYS];

	i = 0;
	tab[0].id = W;
	tab[0].ft_hook_key = &ft_forward;
	tab[1].id = S_;
	tab[1].ft_hook_key = &ft_back;
	tab[2].id = A_;
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
	_player()->norm_pitch = normalise_between2F(posf(-1000, 1000),
		posf(-1, 1), _player()->pitch);
	//printf("==> %f\n", sin(_player()->pitch));
	return (0);
}

int	ft_down_head(void)
{
	_player()->pitch -= 200 * _player()->move_speed;
	if(_player()->pitch < -400)
		_player()->pitch = -400;
	_player()->norm_pitch = normalise_between2F(posf(-1000, 1000),
		posf(-1, 1), _player()->pitch);
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
	if (pos.x >= 0 && pos.y >= 0 && pos.x < _var()->map_width
		&& pos.y < _var()->map_height && _var()->map[pos.y][pos.x] == '1')
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
	if (click_delay())
		return (0);
	printf("je passe ici\n");
	if ((_var()->is_host == CLIENT || _var()->is_host == SERVER) && _player()->id == 0)
	{
		printf("1\n");
		mlx_mouse_show(_mlx()->mlx, _mlx()->mlx_win);
		close(_var()->socket);
		if (_var()->pid > 0)
			kill((pid_t)_var()->pid, SIGKILL);
		_var()->pid = -1;
		click();
		_var()->is_host = NONE;
	}
	if (_var()->mode == GAME)
	{
		printf("2\n");
		restart_player();
		mlx_mouse_show(_mlx()->mlx, _mlx()->mlx_win);
		_var()->mode = MENU;
		_menu()->mode = MENU_START;
		click();
	}
	else if (_var()->mode == MENU)
	{
		printf("3\n");
		if (_menu()->mode == MENU_START)
			ft_black_hole(0);
		if (_menu()->mode == MENU_PLAYER)
			_menu()->mode = MENU_START;
		if (_menu()->mode == MENU_IP)
			_menu()->mode = MENU_PLAYER;
		if (_menu()->mode == MENU_PSEUDO)
			_menu()->mode = MENU_PLAYER;
		click();
	}
	return (0);
}
