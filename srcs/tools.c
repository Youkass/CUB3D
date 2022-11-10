/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:16:19 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/04 16:59:48 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/*
-Cast two int in t_vector2D.
*/
t_vector2D	pos(int x, int y)
{
	return ((t_vector2D){x, y});
}

/*
-Cast two int in t_vector2F.
*/
t_vector2F	posf(float x, float y)
{
	return ((t_vector2F){x, y});
}

t_vector3F	pos3f(float x, float y, float z)
{
	return ((t_vector3F){x, y, z});
}