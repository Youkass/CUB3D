/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:08:36 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/18 17:51:51 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	init_cast(t_obj *player)
{
	_pc()->pos.x = player->x - _player()->x;
	_pc()->pos.y = player->y -_player()->y;
	_pc()->inv_det = 1.0 / (_player()->plane.x * _player()->dy -
			_player()->dx * _player()->plane.y);
	_pc()->trans.x = _pc()->inv_det * (_player()->dy *
			_pc()->pos.x - _player()->dx * _pc()->pos.y);
	_pc()->trans.y = _pc()->inv_det * (-_player()->plane.y *
			_pc()->pos.x + _player()->plane.x * _pc()->pos.y);
	_pc()->sprite_screen_x = (int)((WIN_W / 2) * (1 + _pc()->trans.x
				/ _pc()->trans.y));
	_pc()->move_screen = (int)(vMove / _pc()->trans.y) + _player()->pitch + player->z / _pc()->trans.y;
}
static void	compute_draw(void)
{
	_pc()->size.y = abs((int)(WIN_H / (_pc()->trans.y))) / vDiv;
	_pc()->draw_start.y = -_pc()->size.y / 2 + WIN_H / 2 + _pc()->move_screen;
	if (_pc()->draw_start.y < 0)
		_pc()->draw_start.y = 0;
	_pc()->draw_end.y = _pc()->size.y / 2 + WIN_H / 2 + _pc()->move_screen;
	if (_pc()->draw_end.y >= WIN_H)
		_pc()->draw_end.y = WIN_H;
	_pc()->size.x = abs((int)(WIN_H / (_pc()->trans.y))) / uDiv;
	_pc()->draw_start.x = -_pc()->size.x / 2 + _pc()->sprite_screen_x;
	if (_pc()->draw_start.x < 0)
		_pc()->draw_start.x = 0;
	_pc()->draw_end.x = _pc()->size.x / 2 + _pc()->sprite_screen_x;
	if (_pc()->draw_end.x >= WIN_W)
		_pc()->draw_end.x = WIN_W;
}

static void	draw(t_obj *player)
{
	int	stripe;
	int	y;

	compute_draw();
	stripe = _pc()->draw_start.x;
	while (stripe < _pc()->draw_end.x)
	{
		_pc()->tex.x = (int)(256 * (stripe - (-_pc()->size.x / 2 + _pc()->sprite_screen_x)) * player->sprite.width / _pc()->size.x) / 256;
		if(_pc()->trans.y > 0 && stripe > 0 && stripe < WIN_W && _pc()->trans.y < _var()->zbuffer[stripe])
		{
			y = _pc()->draw_start.y;
			while (y < _pc()->draw_end.y)
			{
				_pc()->d = (y - _pc()->move_screen) * 256 - WIN_H * 128 + _pc()->size.y * 128;
				_pc()->tex.y = ((_pc()->d * player->sprite.height) /_pc()->size.y) / 256;
				ft_put_pixel(_img(), &player->sprite, (t_vector2D){stripe, y}, _pc()->tex);
				y++;
			}
		}
		stripe++;
	}

}

void	player_casting(void)
{
	int	i;

	i = 0;
	while (i < _img()->nb_player)
	{
		init_cast(&(_var()->o_player[i]));
		draw(&(_var()->o_player[i]));
	}
}
