/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:44:57 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

static void	ft_help_hud_if(int index, unsigned long time_attack, int weapon_id)
{
	index = normalise_between(pos(0, _weapon()[weapon_id]->reload_ms),
			pos(0, _weapon()[weapon_id]->shot_frames - 1), time_attack);
	if (weapon_id == KNIFE)
		ft_put_img_to_img_scale(*_img(), _image()->weapons[weapon_id]
		[ATTACK][0], pos(WIN_W / 2 - (_image()->weapons[weapon_id][ATTACK]
				[0].w * 2 / 4) + 200, WIN_H - _image()->weapons[weapon_id]
			[ATTACK][0].h * 2), posf(0.5, 0.5));
	else
		ft_put_img_to_img_scale(*_img(),
			_image()->weapons[weapon_id][ATTACK][index], pos(WIN_W / 2
				- (_image()->weapons[weapon_id][ATTACK][index].w * 2 / 4) + 200,
				WIN_H - _image()->weapons[weapon_id][ATTACK][index].h * 2),
			posf(0.5, 0.5));
}

static void	ft_help_hud_else_if(int index, unsigned long time_reload,
	int weapon_id)
{
	index = normalise_between(pos(0,
				_weapon()[weapon_id]->anim_reloadms), pos(0,
				_weapon()[weapon_id]->reload_frames - 1), time_reload);
	ft_put_img_to_img_scale(*_img(), _image()->weapons[weapon_id][RELOAD]
	[index], pos(WIN_W / 2 - (_image()->weapons[weapon_id][RELOAD][index].w
				* 2 / 4) + 200, WIN_H - _image()->weapons[weapon_id][RELOAD]
		[index].h * 2 + 50), posf(0.5, 0.5));
}

static void	ft_help_hud_else(int weapon_id)
{
	_var()->shot_anim = 0;
	_var()->reload_anim = 0;
	ft_put_img_to_img_scale(*_img(),
		_image()->weapons[weapon_id][NORMAL]
	[0], pos(WIN_W / 2
			- (_image()->weapons[weapon_id][NORMAL]
			[0].w * 2 / 4) + 200, WIN_H - _image()->weapons
		[weapon_id][NORMAL][0].h * 2),
		posf(0.5, 0.5));
}

void	hud_hit_and_touch(void)
{
	if (_player()->touched)
		ft_put_image_to_image(*_img(), _image()->hitmarker, pos(WIN_W / 2 - 8,
				WIN_H / 2 - 8));
	else
		ft_put_image_to_image(*_img(), _image()->crosshair, pos(WIN_W / 2 - 8,
				WIN_H / 2 - 8));
	if (_player()->touched == 1 && get_time(_var()->start_touch) > 100000)
		_player()->touched = 0;
	if (_player()->hitted)
	{
		draw_rectangle(pos(0, 0), pos(WIN_W, 20), (char [4]){0, 34, 250, 250});
		draw_rectangle(pos(0, WIN_H - 20), pos(WIN_W, 20),
			(char [4]){0, 34, 250, 250});
		draw_rectangle(pos(0, 0), pos(20, WIN_H), (char [4]){0, 34, 250, 250});
		draw_rectangle(pos(WIN_W - 20, 0), pos(20, WIN_H),
			(char [4]){0, 34, 250, 250});
	}
	if (_player()->hitted == 1 && get_time(_var()->start_hit) > 100000)
		_player()->hitted = 0;
}

void	hud(void)
{
	unsigned long	time_attack;
	unsigned long	time_reload;
	int				index;
	int				weapon_id;

	time_attack = get_time(_var()->shotanim_start);
	time_reload = get_time(_var()->reloadanim_start);
	index = 0;
	if (_player()->spectate && _player()->spec_id > 0 && _player()->spec_id
		< _var()->linked_players)
		weapon_id = _var()->o_player[_player()->spec_id].weapon_id;
	else
		weapon_id = _player()->weapon_id;
	if (_var()->shot_anim
		&& time_attack < _weapon()[_player()->weapon_id]->reload_ms)
		ft_help_hud_if(index, time_attack, weapon_id);
	else if (_var()->reload_anim
		&& (int)time_reload < _weapon()[_player()->weapon_id]->anim_reloadms)
		ft_help_hud_else_if(index, time_reload, weapon_id);
	else
		ft_help_hud_else(weapon_id);
	hud_hit_and_touch();
	if (_var()->round_state == ROUND_WAIT_START)
		draw_text(ft_itoa(_var()->time_start), pos(WIN_W / 2 - 42, WIN_H / 2),
			(char [4]){0, 34, 250, 250});
}
