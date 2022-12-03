/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:09:46 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 19:10:04 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	ft_return_xp_2(void)
{
	return ((int)(_player2()->hb.hit.pos.x
		* _var()->scale) + _var()->half_scale_offset);
}

int	ft_return_yp_2(void)
{
	return ((int)(_player2()->hb.hit.pos.y * _var()->scale)
			+ _var()->half_scale);
}

float	ft_return_radius_2(void)
{
	return ((_player2()->hb.hit.r) * _var()->scale);
}
