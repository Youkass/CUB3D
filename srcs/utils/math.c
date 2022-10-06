/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:43:05 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/05 16:25:18 by denissereno      ###   ########.fr       */
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