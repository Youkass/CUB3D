/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator2D.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 23:08:15 by denissereno       #+#    #+#             */
/*   Updated: 2022/12/03 17:00:07 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

/*
-	Divide two int vector.
*/
t_vector2D	div_2d(t_vector2D a, t_vector2D b)
{
	return ((t_vector2D){a.x / b.x, a.y / b.y});
}

/*
-	Multiply two int vector.
*/
t_vector2D	mult_2d(t_vector2D a, t_vector2D b)
{
	return ((t_vector2D){a.x * b.x, a.y * b.y});
}

/*
-	Add three float vector.
*/
t_vector3F	add_3f(t_vector3F a, t_vector3F b)
{
	t_vector3F	vec;

	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	vec.z = a.z + b.z;
	return (vec);
}
