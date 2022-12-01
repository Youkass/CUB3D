/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:46:15 by denissereno       #+#    #+#             */
/*   Updated: 2022/12/01 16:45:09 by dasereno         ###   ########.fr       */
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
	_pc()->move_screen = (int)(-300 / _pc()->trans.y) + my_player->pitch
	+ player->x / _pc()->trans.y;
}

static void	compute_draw(void)
{
	_pc()->size.y = abs((int)(WIN_H / (_pc()->trans.y))) / 20;
	_pc()->draw_start.y = -_pc()->size.y / 2 + WIN_H / 2 + _pc()->move_screen;
	if (_pc()->draw_start.y < 0)
		_pc()->draw_start.y = 0;
	_pc()->draw_end.y = _pc()->size.y / 2 + WIN_H / 2 + _pc()->move_screen;
	if (_pc()->draw_end.y >= WIN_H)
		_pc()->draw_end.y = WIN_H;
	_pc()->size.x = abs((int)(WIN_H / (_pc()->trans.y))) / 2;
	_pc()->draw_start.x = -_pc()->size.x / 2 + _pc()->sprite_screen_x;
	if (_pc()->draw_start.x < 0)
		_pc()->draw_start.x = 0;
	_pc()->draw_end.x = _pc()->size.x / 2 + _pc()->sprite_screen_x;
	if (_pc()->draw_end.x >= WIN_W)
		_pc()->draw_end.x = WIN_W;
}

static void	draw_body(t_obj *player, int stripe)
{
	int	y;

	y = _pc()->draw_start.y;
	while (y < _pc()->draw_end.y)
	{
		_pc()->d = (y - _pc()->move_screen) * 256 - WIN_H * 128
		+ _pc()->size.y * 128;
		_pc()->tex.y = ((_pc()->d * _image()->pseudo_img[player->id].h)
			/_pc()->size.y) / 256;
		ft_put_pixel(_img(), &_image()->pseudo_img[player->id],
			(t_vector2D){stripe, y}, _pc()->tex);
		y++;
	}
}

static void	draw(t_obj *player)
{
	int	stripe;

	compute_draw();
	stripe = _pc()->draw_start.x;
	while (stripe < _pc()->draw_end.x)
	{
		_pc()->tex.x = (int)(256 * (stripe - (-_pc()->size.x / 2
					+ _pc()->sprite_screen_x)) * _image()->pseudo_img
		[player->id].w / _pc()->size.x) / 256;
		if (_pc()->trans.y > 0 && stripe > 0 && stripe < WIN_W
			&& _pc()->trans.y < _var()->zbuffer[stripe])
			draw_body(player, stripe);
		stripe++;
	}
}

void	name_casting(void)
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
			draw(&(_var()->sort_player[i]));
		}
		++i;
	}
}
