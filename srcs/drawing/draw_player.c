/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:57:36 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/06 13:25:31 by denissereno      ###   ########.fr       */
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

	vector.x = (_player()->x * (float)_img()->scale)
		+ _img()->half_scale_offset;
	vector.y = (_player()->y * (float)_img()->scale) + _img()->half_scale;
	return (vector);
}

t_vector2D	ft_scnd_vector(void)
{
	t_vector2D	vector;

	vector.x = ((_player()->x * (float)_img()->scale)
		+ _img()->half_scale_offset) + _player()->dx * 10;
	vector.y = (_player()->y * (float)_img()->scale)
		+ (_player()->dy * 10) + _img()->half_scale;
	return (vector);
}

/*
===============================================================================
fonction a ajouter dans un fichier utils_draw_circle.c //TODO
===============================================================================
*/

int	ft_return_xp(void)
{
	return ((int)(_player()->hb.hit.x
		* _img()->scale) + _img()->half_scale_offset);
}

int	ft_return_yp(void)
{
	return ((int)(_player()->hb.hit.y * _img()->scale) + _img()->half_scale);
}

float	ft_return_radius(void)
{
	return ((_player()->hb.hit.radius) * _img()->scale);
}
