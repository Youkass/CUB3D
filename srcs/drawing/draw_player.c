/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:57:36 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/03 13:48:36 by yobougre         ###   ########.fr       */
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
the keyhooks functions (see key_hooks.c), modifying the position by its
singleton.
===============================================================================
*/

void	ft_draw_player()
{
	//t_int	var;

	//var.i = 0;
	//while (var.i < _img()->scale)
	//{
	//	var.j = 0;
	//	while (var.j < _img()->scale)
	//	{
	//		ft_pixel_put((int)(_player()->x * (float)_img()->scale) + var.i + MINIMAP_OFFSET, (int)(_player()->y * (float)_img()->scale) + var.j, 0x00FF0000);
	//		var.j++;
	//	}
	//	var.i++;
	//}
	/*
	DRAW CIRCLE ():
	FIRST ARG : (int)(_player()->hb.hit.x * _img()->scale) + _img()->scale / 2 + MINIMAP_OFFSET
	SCND ARG :  (int)(_player()->hb.hit.y* _img()->scale) + _img()->scale / 2
	THIRD ARG :  (_player()->hb.hit.radius) * _img()->scale, 0xFFFF0000)

	PLOT_LINE ():
	FIRST ARG : (t_vector2D){(_player()->x * (float)_img()->scale) + _img()->scale / 2 + MINIMAP_OFFSET 
	SCND ARG :(_player()->y * (float)_img()->scale) + _img()->scale / 2}
	THIRD ARG :(t_vector2D){((_player()->x * (float)_img()->scale) + _img()->scale / 2 + MINIMAP_OFFSET) + _player()->dx * 10
	FOURTH ARG :  ((_player()->y * (float)_img()->scale)) + (_player()->dy * 10) + _img()->scale / 2}
	FIFTH ARG :  0xcf34eb
	*/

}
