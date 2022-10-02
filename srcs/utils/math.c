/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:43:05 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/02 17:43:15 by denissereno      ###   ########.fr       */
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
