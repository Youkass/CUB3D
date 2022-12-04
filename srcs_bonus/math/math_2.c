/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:58:40 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

/*
-Normalise nb who is between t.x -> t.y to r range. {r.x -> r.y}.
*/
int	normalise_between(t_vector2D r, t_vector2D t, int nb)
{
	return ((int)round((((float)nb - (float)r.x)
				/ ((float)r.y - (float)r.x)) * t.y));
}

float	normalise_between2f(t_vector2F r, t_vector2F t, int nb)
{
	return (2 * (((nb - r.x) / (r.y - r.x)) * t.y) - 1);
}

/*
-Function that calculate the modulo of a by b.
*/
int	mod(int a, int b)
{
	int	r;

	r = a % b;
	if (r < 0)
		return (r + b);
	return (r);
}

/*
-Convert radian to degree.
*/

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
