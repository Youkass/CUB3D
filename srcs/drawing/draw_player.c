/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:57:36 by yobougre          #+#    #+#             */
/*   Updated: 2022/09/29 17:08:46 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

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
