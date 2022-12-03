/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:00:43 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 17:01:07 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

t_vector2F	velocity_get_point(t_vector2F start, t_vector2F velo, int time_ms)
{
	return (add_2f(start, posf(velo.x * time_ms, velo.y * time_ms)));
}

t_vector3F	velocity_get_point3f(t_vector3F start, t_vector3F velo, int time_ms)
{
	return (add_3f(start, pos3f(velo.x * time_ms, velo.y * time_ms, velo.z
				* time_ms)));
}

float	one_dist2f(t_vector2F a, t_vector2F b)
{
	return (sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2)));
}

float	one_dist3f(t_vector3F a, t_vector3F b)
{
	return (sqrtf(powf(a.x - b.x, 3) + powf(a.y - b.y, 3)
			+ powf(a.z - b.z, 3)));
}
