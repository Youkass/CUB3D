/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:57:36 by yobougre          #+#    #+#             */
/*   Updated: 2022/09/28 14:51:54 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	ft_draw_player(t_obj player)
{
	t_int	var;

	var.i = 0;
	while (var.i < 10)
	{
		var.j = 0;
		while (var.j < 10)
		{
			ft_pixel_put(player.x + var.i, player.y + var.j, 0x00FF0000);
			var.j++;
		}
		var.i++;
	}
}
