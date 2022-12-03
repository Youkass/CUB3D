/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:49:41 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 19:21:17 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	ft_next_while_draw_sky(t_vector2D pt)
{
	while (pt.y < WIN_H)
	{
		pt.x = 0;
		while (pt.x < WIN_W)
		{
			ft_put_pixel_color_unsigned(_img(), _var()->colors[0],
				pt.x, pt.y);
			pt.x++;
		}
		pt.y++;
	}
	if (_menu()->draw_pl[0].x != -1 && _menu()->draw_pl[0].y != -1)
		ft_put_sprite_to_images(_menu()->planets[0],
			_menu()->draw_pl[0], (t_vector2D){_menu()->n * 48,
			_menu()->ny * 48}, (t_vector2D){48, 48});
}

void	ft_norme_while_draw_sky(int offst, int pitch, t_vector2D *pl_coord)
{
	t_vector2D	pt;
	t_vector2D	tex;

	pt.y = 0;
	while (pt.y < WIN_H / 2 + pitch)
	{
		tex.y = (((pt.y * 2 * WIN_W / (WIN_H)) / 4)
				- (pitch * 0.8)) + WIN_H / 2;
		pt.x = 0;
		while (pt.x < WIN_W)
		{
			tex.x = pt.x * WIN_W / (4 * WIN_W / 2);
			if (tex.x + offst == pl_coord[0].x && tex.y == 400)
				_menu()->draw_pl[0] = pt;
			tex.x = (tex.x + offst) % WIN_W;
			if (_img() && _image()->bg.img)
				ft_put_pixel(_img(), &_image()->bg, pt, tex);
			pt.x++;
		}
		pt.y++;
	}
	ft_next_while_draw_sky(pt);
}

void	ft_norme_draw_sky(t_vector2D *pl_coord)
{
	double	angle;
	int		offset;
	int		pitch;

	if (_player()->spectate && _player()->spec_id >= 0 && _player()->spec_id
		<= _var()->linked_players)
	{
		angle = atan2(_var()->o_player[_player()->spec_id].dy,
				_var()->o_player[_player()->spec_id].dx);
		pitch = _var()->o_player[_player()->spec_id].pitch;
	}
	else
	{
		angle = atan2(_player()->dy, _player()->dx);
		pitch = _player()->pitch;
	}
	offset = (int)(angle * WIN_W * 2 / (M_PI * 2)) + (WIN_W / 2) * 2;
	ft_norme_while_draw_sky(offset, pitch, pl_coord);
}
