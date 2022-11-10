/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullet_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:08:36 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/10 10:55:30 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	init_cast(int i, t_obj *player)
{
	_pc()->pos.x = player->shott[i].pos3F.x - _player()->x;
	_pc()->pos.y = player->shott[i].pos3F.y -_player()->y;
	_pc()->inv_det = 1.0 / (_player()->plane.x * _player()->dy -
			_player()->dx * _player()->plane.y);
	_pc()->trans.x = _pc()->inv_det * (_player()->dy *
			_pc()->pos.x - _player()->dx * _pc()->pos.y);
	_pc()->trans.y = _pc()->inv_det * (-_player()->plane.y *
			_pc()->pos.x + _player()->plane.x * _pc()->pos.y);
	_pc()->sprite_screen_x = (int)((WIN_W / 2) * (1 + _pc()->trans.x
				/ _pc()->trans.y));
	_pc()->move_screen = (int)((int)player->shott[i].pos3F.z / _pc()->trans.y) + _player()->pitch + _player()->z / _pc()->trans.y;
}

static void	compute_draw(void)
{
	_pc()->size.y = abs((int)(WIN_H / (_pc()->trans.y))) / 5;
	_pc()->draw_start.y = -_pc()->size.y / 2 + WIN_H / 2 + _pc()->move_screen;
	if (_pc()->draw_start.y < 0)
		_pc()->draw_start.y = 0;
	_pc()->draw_end.y = _pc()->size.y / 2 + WIN_H / 2 + _pc()->move_screen;
	if (_pc()->draw_end.y >= WIN_H)
		_pc()->draw_end.y = WIN_H;
	_pc()->size.x = abs((int)(WIN_H / (_pc()->trans.y))) / 5;
	_pc()->draw_start.x = -_pc()->size.x / 2 + _pc()->sprite_screen_x;
	if (_pc()->draw_start.x < 0)
		_pc()->draw_start.x = 0;
	_pc()->draw_end.x = _pc()->size.x / 2 + _pc()->sprite_screen_x;
	if (_pc()->draw_end.x >= WIN_W)
		_pc()->draw_end.x = WIN_W;
}

static void	draw()
{
	int	stripe;
	int	y;

	compute_draw();
	stripe = _pc()->draw_start.x;
	while (stripe < _pc()->draw_end.x)
	{
		_pc()->tex.x = (int)(256 * (stripe - (-_pc()->size.x / 2 + _pc()->sprite_screen_x)) * _image()->bullet.w / _pc()->size.x) / 256;
		if(_pc()->trans.y > 0 && stripe > 0 && stripe < WIN_W && _pc()->trans.y < _var()->zbuffer[stripe])
		{
			y = _pc()->draw_start.y;
			while (y < _pc()->draw_end.y)
			{
				_pc()->d = (y - _pc()->move_screen) * 256 - WIN_H * 128 + _pc()->size.y * 128;
				_pc()->tex.y = ((_pc()->d * _image()->bullet.h) /_pc()->size.y) / 256;
				ft_put_pixel(_img(), &_image()->bullet, (t_vector2D){stripe, y}, _pc()->tex);
				y++;
			}
		}
		stripe++;
	}
}

void	bullet_casting(void)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < _var()->nb_player)
	{
		j = 0;
		if (i == _player()->id)
		{
			j = 0;
			while (j < _player()->shoot_n)
			{
				init_cast(j, _player());
				draw();
				j++;
			}	
		}
		j = 0;
		while (j < _var()->o_player[i].shoot_n)
		{
			if (i == 0)
				init_cast(j, _player());
			else
				init_cast(j, &_var()->o_player[i]);
			draw();
			j++;
		}
		i++;
	}
}
