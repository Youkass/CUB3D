/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:43:05 by denissereno       #+#    #+#             */
/*   Updated: 2022/12/05 19:05:36 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/*
-Function to compute magnitude of a vector.
*/
float	mag(t_vector2F v)
{
	return (sqrt(powf(v.x, 2) + powf(v.y, 2)));
}

/*
-Function to normalize a vector between 0 and 1.
*/
t_vector2F	norm(t_vector2F v)
{
	float	r;

	r = 1 / mag(v);
	return ((t_vector2F){v.x * r, v.y * r});
}

float	rad_to_deg(float rad)
{
	float	deg;

	deg = rad * (180 / M_PI);
	if (deg < 0)
		deg += 360;
	return (deg);
}

float	deg_to_rad(float deg)
{
	float	rad;

	rad = deg * (M_PI / 180);
	return (rad);
}

void	set_pos(t_vector2D it, t_vector2F dir, t_vector2F plane)
{
	_player()->dx = dir.x;
	_player()->x = it.x + 0.1;
	_player()->y = it.y + 0.5;
	_player()->dy = dir.y;
	_ray()->plane = plane;
}
