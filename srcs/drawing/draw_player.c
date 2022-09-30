/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:57:36 by yobougre          #+#    #+#             */
/*   Updated: 2022/09/30 13:32:03 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void plot_line (int x0, int y0, int x1, int y1, int color)
{
	int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
	int err = dx + dy, e2; /* error value e_xy */
	for (;;){  /* loop */
	ft_pixel_put(x0,y0, color);
	if (x0 == x1 && y0 == y1) break;
	e2 = 2 * err;
	if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
	if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}

/*
===============================================================================
this is the function that will draw our player on the 2D map.

we need to use a flag for the first drawing, because we're getting the player
position from the cartesian plan, then, we'll move our player directly by
the keyhooks functions (see key_hooks.c), modifying the position by its
singleton.
===============================================================================
*/
void	ft_draw_player(t_obj player)
{
	t_int	var;
	static int	flag = 0;

	var.i = 0;
	if (!flag)
	{
		_player()->x = player.x;
		_player()->y = player.y;
		_player()->dx = cos(_player()->angle) * 5;
		_player()->dy = sin(_player()->angle) * 5;
		++flag;
	}
	while (var.i < 10)
	{
		var.j = 0;
		while (var.j < 10)
		{
			ft_pixel_put(_player()->x + var.i, _player()->y + var.j, 0x00FF0000);
			var.j++;
		}
		var.i++;
	}
	plot_line(_player()->x + 5 , _player()->y + 5, (_player()->x + 5) + _player()->dx * 5, (_player()->y + 5) + _player()->dy * 5, 0xFF000000);
}
