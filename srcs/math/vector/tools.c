/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 23:11:29 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/31 23:44:11 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

t_vector2F	dist_2f(t_vector2F a, t_vector2F b)
{
	return (posf(b.x - a.x, b.y - a.y));
}

t_vector2F	velocity_ms(t_vector2F dist, float time_ms)
{
	return (posf(dist.x / time_ms, dist.y / time_ms));
}

t_vector2F	velocity_get_point(t_vector2F start, t_vector2F velo, int time_ms)
{
	return (add_2f(start, posf(velo.x * time_ms, velo.y * time_ms)));
}