/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:16:19 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/20 14:52:26 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/*
-Cast two int in t_vector2D.
*/
t_vector2D	pos(int x, int y)
{
	t_vector2D	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

/*
-Cast two int in t_vector2F.
*/
t_vector2F	posf(float x, float y)
{
	t_vector2F	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

t_vector3F	pos3f(float x, float y, float z)
{
	t_vector3F	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}
