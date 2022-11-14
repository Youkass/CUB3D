/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:57:36 by yobougre          #+#    #+#             */
/*   Updated: 2022/11/14 18:22:22 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void plot_line (t_vector2D a, t_vector2D b, int color)
{
	int dx =  abs (b.x - a.x), sx = a.x < b.x ? 1 : -1;
	int dy = -abs (b.y - a.y), sy = a.y < b.y ? 1 : -1; 
	int err = dx + dy, e2; /* error value e_xy */
	for (;;){  /* loop */
	ft_pixel_put(a.x,a.y, color);
	if (a.x == b.x && a.y == b.y) break;
	e2 = 2 * err;
	if (e2 >= dy) { err += dy; a.x += sx; } /* e_xy+e_x > 0 */
	if (e2 <= dx) { err += dx; a.y += sy; } /* e_xy+e_y < 0 */
  }
}

/*
===============================================================================
this is the function that will draw our player on the 2D map.

we need to use a flag for the first drawing, because we're getting the player
position from the cartesian plan, then, we'll move our player directly by
the keyhooks functions {see key_hooks.c}, modifying the position by its
singleton.
===============================================================================
*/

t_vector2D	ft_first_vector(void)
{
	t_vector2D	vector;

	vector.x = (_player()->x * (float)_var()->scale)
		+ _var()->half_scale_offset;
	vector.y = (_player()->y * (float)_var()->scale) + _var()->half_scale;
	return (vector);
}

t_vector2D	ft_scnd_vector(void)
{
	t_vector2D	vector;

	vector.x = ((_player()->x * (float)_var()->scale)
		+ _var()->half_scale_offset) + _player()->dx * 10;
	vector.y = (_player()->y * (float)_var()->scale)
		+ (_player()->dy * 10) + _var()->half_scale;
	return (vector);
}

/*
===============================================================================
fonction a ajouter dans un fichier utils_draw_circle.c //TODO
===============================================================================
*/

int	ft_return_xp(t_obj *player, t_obj *my_player)
{
	player->hb.hit.pos.x = player->x;
	return ((int)(player->hb.hit.pos.x
		* _var()->scale) + _var()->half_scale_offset + _var()->map_width * _var()->scale - my_player->x * _var()->scale - 420);
}

int	ft_return_yp(t_obj *player, t_obj *my_player)
{
	player->hb.hit.pos.y = player->y;
	return ((int)(player->hb.hit.pos.y * _var()->scale) + _var()->half_scale + _var()->map_height * _var()->scale - my_player->y * _var()->scale - 150);
}

float	ft_return_radius(t_obj *player)
{
	return ((player->hb.hit.r) * _var()->scale);
}

int	ft_return_xp_2(void)
{
	return ((int)(_player2()->hb.hit.pos.x
		* _var()->scale) + _var()->half_scale_offset);
}

int	ft_return_yp_2(void)
{
	return ((int)(_player2()->hb.hit.pos.y * _var()->scale) + _var()->half_scale);
}

float	ft_return_radius_2(void)
{
	return ((_player2()->hb.hit.r) * _var()->scale);
}
