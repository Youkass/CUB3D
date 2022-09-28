/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:57:36 by yobougre          #+#    #+#             */
/*   Updated: 2022/09/28 11:09:46 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	ft_draw_player(void)
{
	t_int	var;

	var.i = 0;
	while (var.i < 10)
	{
		var.j = 0;
		while (var.j < 10)
		{
			ft_pixel_put(_player()->x + var.i, _player()->y + var.j, 0x00FF0000);
			var.j++;
		}
		//ft_pixel_put(_player()->x + var.i, _player()->y, 0x00FF0000);
		var.i++;
	}
	mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win, _img()->img, 0, 0);
}
