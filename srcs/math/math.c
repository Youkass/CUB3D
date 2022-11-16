/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:43:05 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/16 01:23:12 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"
#include <math.h>

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

/*
-Function that return the max between a or b.
*/
float	max_f(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

/*
-Function that return the min between a or b.
*/
float	min_f(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}
/*
-Function that return the min between a or b.
*/
float	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

/*
-Normalise nb who is between t.x -> t.y to r range. {r.x -> r.y}.
*/
int	normalise_between(t_vector2D r, t_vector2D t, int nb)
{
	return ((int)round((((float)nb - (float)r.x) / ((float)r.y - (float)r.x)) * t.y));
}

float	normalise_between2F(t_vector2F r, t_vector2F t, int nb)
{
	return (2 * (((nb - r.x) / (r.y - r.x)) * t.y) - 1);
	//return (((nb - r.x) / (r.y - r.x)) * t.y);
}
/*
-Function that calculate the modulo of a by b.
*/
int mod(int a, int b)
{
    int r;
	
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