/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 23:11:29 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/13 17:42:41 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

t_vector2F	dist_2f(t_vector2F a, t_vector2F b)
{
	return (posf(b.x - a.x, b.y - a.y));
}

t_vector3F	dist_3f(t_vector3F a, t_vector3F b)
{
	return (pos3f(b.x - a.x, b.y - a.y, b.z - a.z));
}

t_vector2F	velocity_ms(t_vector2F dist, float time_ms)
{
	return (posf(dist.x / time_ms, dist.y / time_ms));
}

t_vector3F	velocity_ms3F(t_vector3F dist, float time_ms)
{
	return (pos3f(dist.x / time_ms, dist.y / time_ms, dist.z / time_ms));
}

float	get_time_velo3F(float dist, float time_ms_per_unit)
{
	return (dist * time_ms_per_unit);
}

t_vector2F	velocity_get_point(t_vector2F start, t_vector2F velo, int time_ms)
{
	return (add_2f(start, posf(velo.x * time_ms, velo.y * time_ms)));
}

t_vector3F	velocity_get_point3F(t_vector3F start, t_vector3F velo, int time_ms)
{
	return (add_3f(start, pos3f(velo.x * time_ms, velo.y * time_ms, velo.z * time_ms)));
}

float	one_dist2F(t_vector2F a, t_vector2F b)
{
	return (sqrtf( powf(a.x - b.x, 2) + powf(a.y - b.y, 2)));
}

float	one_dist3F(t_vector3F a, t_vector3F b)
{
	return (sqrtf(powf(a.x - b.x, 3) + powf(a.y - b.y, 3) + powf(a.z - b.z, 3)));
}