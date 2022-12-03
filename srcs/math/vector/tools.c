/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 23:11:29 by denissereno       #+#    #+#             */
/*   Updated: 2022/12/03 17:01:04 by dasereno         ###   ########.fr       */
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

t_vector3F	velocity_ms3f(t_vector3F dist, float time_ms)
{
	return (pos3f(dist.x / time_ms, dist.y / time_ms, dist.z / time_ms));
}

float	get_time_velo3f(float dist, float time_ms_per_unit)
{
	return (dist * time_ms_per_unit);
}
