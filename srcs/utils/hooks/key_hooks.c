/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:55:05 by yobougre          #+#    #+#             */
/*   Updated: 2022/12/03 20:38:08 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

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

void	reload_hook(void)
{
	int	needed;

	if (_var()->mode == GAME && _player()->full_ammo[_player()->weapon_id]
		> 0 && _player()->ammo[_player()->weapon_id] < 15
		&& _player()->weapon_id != KNIFE)
	{
		needed = abs(_player()->ammo[_player()->weapon_id] - 15);
		if (_player()->full_ammo[_player()->weapon_id] <= needed)
			needed = _player()->full_ammo[_player()->weapon_id];
		_player()->full_ammo[_player()->weapon_id] -= needed;
		_player()->ammo[_player()->weapon_id] += needed;
		_var()->reload_anim = 1;
		_var()->reloadanim_start = get_clock(_var()->clock);
	}
}

void	mouse_menu(void)
{
	if (_var()->key[mouse])
	{
		if (_menu()->mode == INTRO)
			_menu()->mode = MENU_START;
		if (_var()->mode == GAME && _player()->can_shoot && _player()->shoot_n
			< MAX_BULLET && _player()->ammo[_player()->weapon_id] > 0)
		{
			ft_play_own_shot();
			_player()->can_shoot = 0;
			_player()->is_shooting = 1;
			--_player()->ammo[_player()->weapon_id];
			_player()->start_reload = get_clock(_var()->clock);
			shoot();
		}
	}
}

void	crouch_sprint(void)
{
	if (_var()->key[space])
	{
		if (_menu()->mode == INTRO)
			_menu()->mode = MENU_START;
		if (_var()->is_host == SERVER && _menu()->mode == MENU_LOBBY && _var()
			->mode != GAME && is_neutral())
			_player()->is_start = 1;
	}
	if (_var()->key[maj] && _var()->mode == GAME)
		crouch(1);
	else if (!_var()->key[maj] && _var()->mode == GAME)
		crouch(0);
}

void	open_door(void)
{
	t_vector2F	target;

	target.x = _player()->x + (_player()->dx * 1);
	target.y = _player()->y + (_player()->dy * 1);
	if (_var()->map[(int)target.y][(int)target.x] == 'D' && !click_delay())
	{
		click();
		_var()->map[(int)target.y][(int)target.x] = 'E';
	}
	else if (_var()->map[(int)target.y][(int)target.x] == 'E' && !click_delay())
	{
		click();
		_var()->map[(int)target.y][(int)target.x] = 'D';
	}
}

void	key_hook(void)
{
	if (_var()->key[esc])
		ft_escape();
	if (!(_player()->is_dead || _var()->freeze || click_delay()))
	{
		movements();
		weapons();
	}
	if (_var()->key[e])
		open_door();
	mouse_menu();
	crouch_sprint();
	if (_player()->id == 0 && _var()->key[maj] && _var()->mode == MENU)
	{
		click();
		_var()->restart = 1;
	}
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
