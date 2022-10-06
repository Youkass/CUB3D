/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:08:36 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/06 13:28:36 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

#define uDiv 2
#define vDiv 1.5
#define vMove 128 / 2

void	ft_put_pixel(t_data *a, t_data *b, t_vector2D pos_a, t_vector2D pos_b)
{
	if (b->addr[((pos_b.y *b->line_length)  + (pos_b.x * 4)) + 3] != -1)
	{
		a->addr[pos_a.y * a->line_length + pos_a.x * 4] = b->addr[(pos_b.y *b->line_length)  + (pos_b.x * 4)];
		a->addr[(pos_a.y * a->line_length + pos_a.x * 4) + 1] = b->addr[((pos_b.y *b->line_length)  + (pos_b.x * 4)) + 1];
		a->addr[(pos_a.y * a->line_length + pos_a.x * 4) + 2] = b->addr[((pos_b.y *b->line_length)  + (pos_b.x * 4)) + 2];
		a->addr[(pos_a.y * a->line_length + pos_a.x * 4) + 3] = b->addr[((pos_b.y *b->line_length)  + (pos_b.x * 4)) + 3];
	}
}

void	ft_put_pixel_color(t_data *a, char color[4], int x, int y)
{
	if (color[3] != -1)
	{
		a->addr[y * a->line_length + x * 4] = color[0];
		a->addr[(y * a->line_length + x * 4) + 1] = color[1];
		a->addr[(y * a->line_length + x * 4) + 2] = color[2];
		a->addr[(y * a->line_length + x * 4) + 3] = color[3];
	}
}

void	player_casting(void)
{
	_pc()->pos.x = (double)_player2()->x - (double)_player()->x;
	_pc()->pos.y = (double)(_player2()->y - _player()->y);

	_pc()->inv_det = 1.0 / (_player()->plane.x * _player()->dy - _player()->dx * _player()->plane.y);
	_pc()->trans.x = _pc()->inv_det * (_player()->dy * _pc()->pos.x - _player()->dx * _pc()->pos.y);
	_pc()->trans.y = _pc()->inv_det * (-_player()->plane.y * _pc()->pos.x + _player()->plane.x * _pc()->pos.y);

	_pc()->sprite_screen_x = (int)((WIN_W / 2) * (1 + _pc()->trans.x / _pc()->trans.y));

	int vMoveScreen = (int)(vMove / _pc()->trans.y);
	_pc()->size.y = abs((int)(WIN_H / (_pc()->trans.y))) / vDiv;

	_pc()->draw_start.y = -_pc()->size.y / 2 + WIN_H / 2 + vMoveScreen;
    if(_pc()->draw_start.y < 0)
		_pc()->draw_start.y = 0;
	_pc()->draw_end.y = _pc()->size.y / 2 + WIN_H / 2 + vMoveScreen;
    if(_pc()->draw_end.y >= WIN_H)
		_pc()->draw_end.y = WIN_H - 1;

	_pc()->size.x = abs((int)(WIN_H / (_pc()->trans.y)))  / uDiv;
	_pc()->draw_start.x = -_pc()->size.x / 2 + _pc()->sprite_screen_x;
	if(_pc()->draw_start.x < 0)
		_pc()->draw_start.x = 0;
	_pc()->draw_end.x = _pc()->size.x / 2 + _pc()->sprite_screen_x;
	if(_pc()->draw_end.x >= WIN_W)
		_pc()->draw_end.x = WIN_W - 1;
	for(int stripe = _pc()->draw_start.x; stripe < _pc()->draw_end.x; stripe++)
	{
		_pc()->tex.x = (int)(256 * (stripe - (-_pc()->size.x / 2 + _pc()->sprite_screen_x)) * _player2()->sprite.width / _pc()->size.x) / 256;
		if(_pc()->trans.y > 0 && stripe > 0 && stripe < WIN_W && _pc()->trans.y < _var()->zbuffer[stripe])
		{
			for(int y = _pc()->draw_start.y; y < _pc()->draw_end.y; y++)
			{
				_pc()->d = (y - vMoveScreen) * 256 - WIN_H * 128 +_pc()->size.y * 128;
				_pc()->tex.y = ((_pc()->d * _player2()->sprite.height) /_pc()->size.y) / 256;
				ft_put_pixel(_img(), &_player2()->sprite, (t_vector2D){stripe, y}, _pc()->tex); 
			}
		}
	}
}