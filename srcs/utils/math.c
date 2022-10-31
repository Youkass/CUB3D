/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:43:05 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/30 02:10:44 by denissereno      ###   ########.fr       */
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

/*
-Function that calculate the modulo of a by b.
*/
int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

/*
-Convert radian to degree.
*/

float	rad_to_deg(float rad)
{
	float	res;

	res = rad * (180 / M_PI);
	if (res < 0)
		res += 360;
	return (res);
}


/*
-	Divide two float vector.
*/

t_vector2F div_2F(t_vector2F a, t_vector2F b)
{
	return ((t_vector2F){a.x / b.x, a.y / b.y});
}

/*
-	Multiply two float vector.
*/

t_vector2F mult_2F(t_vector2F a, t_vector2F b)
{
	return ((t_vector2F){a.x * b.x, a.y * b.y});
}

/*
-	Divide two int vector.
*/

t_vector2D div_2D(t_vector2D a, t_vector2D b)
{
	return ((t_vector2D){a.x / b.x, a.y / b.y});
}

/*
-	Multiply two int vector.
*/

t_vector2D mult_2D(t_vector2D a, t_vector2D b)
{
	return ((t_vector2D){a.x * b.x, a.y * b.y});
}

float	fdot(t_vector2F a, t_vector2F b)
{
	return ((a.x * b.x) + (a.y * b.y));
}

t_vector2F	sub_2f(t_vector2F a, t_vector2F b)
{
	return ((t_vector2F){a.x - b.x, a.y - b.y});
}

t_vector2F	add_2f(t_vector2F a, t_vector2F b)
{
	return ((t_vector2F){a.x + b.x, a.y + b.y});
}
