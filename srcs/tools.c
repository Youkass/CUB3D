/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:16:19 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/31 23:15:41 by denissereno      ###   ########.fr       */
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