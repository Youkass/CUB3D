/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:57:36 by yobougre          #+#    #+#             */
/*   Updated: 2022/09/30 10:29:45 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/*
===============================================================================
this is the function that will draw our player on the 2D map.

we need to use a flag for the first drawing, because we're getting the player
position from the cartesian plan, then, we'll move our player directly by
the keyhooks functions (see key_hooks.c), and modifying the position by its
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
}
