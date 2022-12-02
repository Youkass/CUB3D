/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:08:36 by denissereno       #+#    #+#             */
/*   Updated: 2022/12/02 13:30:22 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	init_cast(t_obj *player, t_obj *my_player)
{
	_pc()->pos.x = player->x - my_player->x;
	_pc()->pos.y = player->y - my_player->y;
	_pc()->inv_det = 1.0 / (my_player->plane.x * my_player->dy
		- my_player->dx * my_player->plane.y);
	_pc()->trans.x = _pc()->inv_det * (my_player->dy
		* _pc()->pos.x - my_player->dx * _pc()->pos.y);
	_pc()->trans.y = _pc()->inv_det * (-my_player->plane.y
		* _pc()->pos.x + my_player->plane.x * _pc()->pos.y);
	_pc()->sprite_screen_x = (int)((WIN_W / 2) * (1 + _pc()->trans.x
			/ _pc()->trans.y));
	if (player->is_crouching)
		_pc()->move_screen = (int)((-player->z + _player()->z + 150 + 70)
			/ _pc()->trans.y) + my_player->pitch + player->z / _pc()->trans.y;
	else
		_pc()->move_screen = (int)((-player->z + _player()->z + 150)
			/ _pc()->trans.y) + my_player->pitch + player->z / _pc()->trans.y;
}

static void	compute_draw(t_obj *player)
{
	if (player->is_crouching)
		_pc()->size.y = abs((int)(WIN_H / (_pc()->trans.y))) / 2.5;
	else
		_pc()->size.y = abs((int)(WIN_H / (_pc()->trans.y))) / 1.5;
	_pc()->draw_start.y = -_pc()->size.y / 2 + WIN_H / 2 + _pc()->move_screen;
	if (_pc()->draw_start.y < 0)
		_pc()->draw_start.y = 0;
	_pc()->draw_end.y = _pc()->size.y / 2 + WIN_H / 2 + _pc()->move_screen;
	if (_pc()->draw_end.y >= WIN_H)
		_pc()->draw_end.y = WIN_H;
	_pc()->size.x = abs((int)(WIN_H / (_pc()->trans.y))) / 1.5;
	_pc()->draw_start.x = -_pc()->size.x / 2 + _pc()->sprite_screen_x;
	if (_pc()->draw_start.x < 0)
		_pc()->draw_start.x = 0;
	_pc()->draw_end.x = _pc()->size.x / 2 + _pc()->sprite_screen_x;
	if (_pc()->draw_end.x >= WIN_W)
		_pc()->draw_end.x = WIN_W;
}

static void	draw(t_obj *player, t_obj *my_player)
{
	int	stripe;
	int	y;

	choose_mode(player, my_player);
	compute_draw(player);
	stripe = _pc()->draw_start.x;
	while (stripe < _pc()->draw_end.x)
	{
		choose_tex(_var()->tex_mode, _var()->walk_tex, stripe, _var()->tex_dir);
		if (_pc()->trans.y > 0 && stripe > 0 && stripe < WIN_W && _pc()->trans.y
			< _var()->zbuffer[stripe])
		{
			y = _pc()->draw_start.y;
			while (y < _pc()->draw_end.y)
			{
				_pc()->d = (y - _pc()->move_screen) * 256 - WIN_H * 128
				+ _pc()->size.y * 128;
				put_pixel_from_mode(player, stripe, y);
				y++;
			}
		}
		stripe++;
	}
}

void	sort_by_distance(t_obj *player)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < _var()->linked_players)
	{
		_var()->sort_player[i] = _var()->o_player[i];
		i++;
	}
	i = 0;
	while (i < _var()->linked_players)
	{
		j = i + 1;
		while (j < _var()->linked_players)
		{
			swap_pl(player, i, j);
			j++;
		}
		i++;
	}
}

void	player_casting(void)
{
	int		i;
	t_obj	player;

	i = 0;
	if (_player()->spectate && _player()->spec_id >= 0 && _player()->spec_id
		< _var()->linked_players)
		player = _var()->o_player[_player()->spec_id];
	else
		player = *_player();
	sort_by_distance(&player);
	while (i < _var()->linked_players)
	{
		if (_var()->sort_player[i].id != player.id)
		{
			init_cast(&(_var()->sort_player[i]), &player);
			draw(&(_var()->sort_player[i]), &player);
		}
		++i;
	}
}
