/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator2F.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 23:08:15 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/04 16:59:31 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

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
-	Scalar two float vector.
*/

float	fdot(t_vector2F a, t_vector2F b)
{
	return ((a.x * b.x) + (a.y * b.y));
}

/*
-	Substract two float vector.
*/

t_vector2F	sub_2f(t_vector2F a, t_vector2F b)
{
	return ((t_vector2F){a.x - b.x, a.y - b.y});
}

/*
-	Add two float vector.
*/

t_vector2F	add_2f(t_vector2F a, t_vector2F b)
{
	return ((t_vector2F){a.x + b.x, a.y + b.y});
}


/*
-	Add three float vector.
*/

t_vector3F	add_3f(t_vector3F a, t_vector3F b)
{
	return ((t_vector3F){a.x + b.x, a.y + b.y, a.z + b.z});
}
