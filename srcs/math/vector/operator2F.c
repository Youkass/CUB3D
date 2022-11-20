/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator2F.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 23:08:15 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/20 14:49:01 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

/*
-	Divide two float vector.
*/

t_vector2F div_2F(t_vector2F a, t_vector2F b)
{
	t_vector2F vec;

	vec.x = a.x / b.x;
	vec.y = a.y / b.y;
	return (vec);
}

/*
-	Multiply two float vector.
*/

t_vector2F mult_2F(t_vector2F a, t_vector2F b)
{
	t_vector2F vec;

	vec.x = a.x * b.x;
	vec.y = a.y * b.y;
	return (vec);
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
	t_vector2F vec;

	vec.x = a.x - b.x;
	vec.y = a.y - b.y;
	return (vec);
}

/*
-	Add two float vector.
*/

t_vector2F	add_2f(t_vector2F a, t_vector2F b)
{
	t_vector2F vec;

	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	return (vec);
}


/*
-	Add three float vector.
*/

t_vector3F	add_3f(t_vector3F a, t_vector3F b)
{
	t_vector3F vec;

	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	vec.z = a.z + b.z;
	return (vec);
}
