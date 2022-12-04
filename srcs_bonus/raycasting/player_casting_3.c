/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_casting_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:03:38 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

void	choose_tex(int tex_mode, int walk_tex, int stripe, int tex_dir)
{
	if (!tex_mode)
		_pc()->tex.x = (int)(256 * (stripe - (-_pc()->size.x / 2
					+ _pc()->sprite_screen_x)) * _image()->dsprite[tex_dir].w
			/ _pc()->size.x) / 256;
	else if (tex_mode == 1)
		_pc()->tex.x = (int)(256 * (stripe - (-_pc()->size.x / 2
					+ _pc()->sprite_screen_x)) * ((_image()->walk_sprite
				[walk_tex].w / 16)) / _pc()->size.x) / 256;
	else
		_pc()->tex.x = (int)(256 * (stripe - (-_pc()->size.x / 2
					+ _pc()->sprite_screen_x)) * ((_image()->death_sprite.w
					/ 16)) / _pc()->size.x) / 256;
}

void	normal_player(t_obj *player, int stripe, int y)
{
	_pc()->tex.y = ((_pc()->d * _image()->dsprite[_var()->tex_dir].h)
		/ _pc()->size.y) / 256;
	if (player->team == TEAM_BLUE)
		ft_put_pixel(_img(), &_image()->dsprite[_var()->tex_dir],
			pos(stripe, y), _pc()->tex);
	else
		ft_put_pixel(_img(), &_image()->dsprite_red[_var()->tex_dir],
			pos(stripe, y), _pc()->tex);
}

void	walking_player(t_obj *player, int stripe, int y)
{
	_pc()->tex.y = ((_pc()->d * _image()->walk_sprite[_var()->walk_tex].h)
		/_pc()->size.y) / 256;
	if (player->team == TEAM_BLUE)
		ft_put_pixel(_img(), &_image()->walk_sprite[_var()->walk_tex],
			pos(stripe, y), pos(_pc()->tex.x + 43 * _var()->walk_n,
				_pc()->tex.y));
	else
		ft_put_pixel(_img(), &_image()->walk_sprite_red[_var()->walk_tex],
			pos(stripe, y), pos(_pc()->tex.x + 43 * _var()->walk_n,
				_pc()->tex.y));
}

void	dead_player(t_obj *player, int stripe, int y)
{
	_pc()->tex.y = ((_pc()->d * _image()->death_sprite.h) / _pc()->size.y)
	/ 256;
	if (player->team == TEAM_BLUE)
		ft_put_pixel(_img(), &_image()->death_sprite, pos(stripe, y + 5),
			pos(_pc()->tex.x + 39 * player->death_n, _pc()->tex.y));
	else
		ft_put_pixel(_img(), &_image()->death_sprite_red, pos(stripe, y
				+ 5), pos(_pc()->tex.x + 39 * player->death_n,
				_pc()->tex.y));
}
