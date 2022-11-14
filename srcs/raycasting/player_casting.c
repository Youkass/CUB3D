/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:08:36 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/13 18:21:28 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	init_cast(t_obj *player, t_obj *my_player)
{
	_pc()->pos.x = player->x - my_player->x;
	_pc()->pos.y = player->y -my_player->y;
	_pc()->inv_det = 1.0 / (my_player->plane.x * my_player->dy -
			my_player->dx * my_player->plane.y);
	_pc()->trans.x = _pc()->inv_det * (my_player->dy *
			_pc()->pos.x - my_player->dx * _pc()->pos.y);
	_pc()->trans.y = _pc()->inv_det * (-my_player->plane.y *
			_pc()->pos.x + my_player->plane.x * _pc()->pos.y);
	_pc()->sprite_screen_x = (int)((WIN_W / 2) * (1 + _pc()->trans.x
				/ _pc()->trans.y));
	if (player->is_crouching)
		_pc()->move_screen = (int)((-player->z + _player()->z + 150 + 70) / _pc()->trans.y) + my_player->pitch + player->z / _pc()->trans.y;
	else
		_pc()->move_screen = (int)((-player->z + _player()->z + 150) / _pc()->trans.y) + my_player->pitch + player->z / _pc()->trans.y;
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
	int	tex_dir;
	int	tex_mode;
	int	walk_tex;

	tex_mode = 0;
	tex_dir  = mod(normalise_between((t_vector2D){0, 360}, (t_vector2D){0, 16}, player->angle) +
	normalise_between((t_vector2D){0, 360}, (t_vector2D){0, 16}, rad_to_deg(atan2(my_player->y - player->y, my_player->x - player->x))), 16);
	if (player->is_walking == 1)
	{
		tex_mode = 1;
		walk_tex =  mod(normalise_between((t_vector2D){0, 360}, (t_vector2D){0, 8}, player->angle) +
		normalise_between((t_vector2D){0, 360}, (t_vector2D){0, 8}, rad_to_deg(atan2(my_player->y - player->y, my_player->x - player->x))), 8);
	}
	if (player->is_dead == 1)
	{
		tex_mode = 2;
		//tex_sp =  mod(normalise_between((t_vector2D){0, 360}, (t_vector2D){0, 8}, _player2()->angle) +
		//normalise_between((t_vector2D){0, 360}, (t_vector2D){0, 8}, rad_to_deg(atan2(my_player->y - _player2()->y, my_player->x - _player2()->x))), 8);
	}
	compute_draw(player);
	stripe = _pc()->draw_start.x;
	while (stripe < _pc()->draw_end.x)
	{
		if (!tex_mode)
			_pc()->tex.x = (int)(256 * (stripe - (-_pc()->size.x / 2 + _pc()->sprite_screen_x)) * _image()->dsprite[tex_dir].w / _pc()->size.x) / 256;
		else if (tex_mode == 1)
			_pc()->tex.x = (int)(256 * (stripe - (-_pc()->size.x / 2 + _pc()->sprite_screen_x)) * ((_image()->walk_sprite[walk_tex].w / 16)) / _pc()->size.x) / 256;
		else
			_pc()->tex.x = (int)(256 * (stripe - (-_pc()->size.x / 2 + _pc()->sprite_screen_x)) * ((_image()->death_sprite.w / 16)) / _pc()->size.x) / 256;
		if(_pc()->trans.y > 0 && stripe > 0 && stripe < WIN_W && _pc()->trans.y < _var()->zbuffer[stripe])
		{
			y = _pc()->draw_start.y;
			while (y < _pc()->draw_end.y)
			{
				_pc()->d = (y - _pc()->move_screen) * 256 - WIN_H * 128 + _pc()->size.y * 128;
				if (!tex_mode)
				{
					_pc()->tex.y = ((_pc()->d * _image()->dsprite[tex_dir].h) /_pc()->size.y) / 256;
					if (player->team == TEAM_BLUE)
						ft_put_pixel(_img(), &_image()->dsprite[tex_dir], pos(stripe, y), _pc()->tex);
					else
						ft_put_pixel(_img(), &_image()->dsprite_red[tex_dir], pos(stripe, y), _pc()->tex);
				}
				else if (tex_mode == 1)
				{
					_pc()->tex.y = ((_pc()->d * _image()->walk_sprite[0].h) /_pc()->size.y) / 256;
					if (player->team == TEAM_BLUE)
						ft_put_pixel(_img(), &_image()->walk_sprite[walk_tex], pos(stripe, y), pos(_pc()->tex.x + 43 * _var()->walk_n, _pc()->tex.y));
					else
						ft_put_pixel(_img(), &_image()->walk_sprite_red[walk_tex], pos(stripe, y), pos(_pc()->tex.x + 43 * _var()->walk_n, _pc()->tex.y));
				}
				else
				{
					_pc()->tex.y = ((_pc()->d * _image()->death_sprite.h) /_pc()->size.y) / 256;
					if (player->team == TEAM_BLUE)
						ft_put_pixel(_img(), &_image()->death_sprite, pos(stripe, y + 5), pos(_pc()->tex.x + 39 * player->death_n, _pc()->tex.y));
					else
						ft_put_pixel(_img(), &_image()->death_sprite_red, pos(stripe, y + 5), pos(_pc()->tex.x + 39 * player->death_n, _pc()->tex.y));
				}
				y++;
			}
		}
		stripe++;
	}
}

int	compute_distance(t_vector2F a, t_vector2F b)
{
	return ((int)(fabsf(b.x - a.x) + fabsf(b.y - a.y)));
}

void	sort_by_distance(t_obj *player)
{
	int		i;
	int		j;
	t_obj	tmp;

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
			if (compute_distance((t_vector2F){player->x, player->y}, (t_vector2F){_var()->sort_player[j].x, _var()->sort_player[j].y}) >
			compute_distance((t_vector2F){player->x, player->y}, (t_vector2F){_var()->sort_player[i].x, _var()->sort_player[i].y}))
			{
				tmp = _var()->sort_player[i];
				_var()->sort_player[i] = _var()->sort_player[j];
				_var()->sort_player[j] = tmp;
			}		
			j++;
		}
		i++;
	}
}

void	player_casting(void)
{
	int	i;
	t_obj	player;

	i = 0;
	if (_player()->spectate && _player()->spec_id >= 0 && _player()->spec_id < 
	_var()->linked_players)
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
