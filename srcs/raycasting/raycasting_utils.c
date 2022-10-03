/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:43:03 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/03 15:09:55 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int intersects(t_circle circle, t_rect rect)
{
	t_vector2F	circle_dist;
	float		corner;

    circle_dist.x = fabs(circle.x - rect.x);
    circle_dist.y = fabs(circle.y - rect.y);

    if (circle_dist.x > (rect.width/2 + circle.radius))
		return (0);
    if (circle_dist.y > (rect.height/2 + circle.radius))
		return (0);

    if (circle_dist.x <= (rect.width/2))
		return (1); 
    if (circle_dist.y <= (rect.height/2))
		return (1);

    corner = pow((circle_dist.x - rect.width/2), 2) + pow((circle_dist.y - rect.height/2), 2);
    return (corner <= (pow(circle.radius, 2)));
}
