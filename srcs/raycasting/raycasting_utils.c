/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:43:03 by yobougre          #+#    #+#             */
/*   Updated: 2022/09/29 23:43:09 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

float	ray_dist(t_vector2F a, t_vector2F b, float angle)
{
	(void)angle;
	 return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y)));
}
