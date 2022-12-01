/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator2D.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 23:08:15 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/30 11:41:56 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

/*
-	Divide two int vector.
*/
t_vector2D div_2d(t_vector2D a, t_vector2D b)
{
	return ((t_vector2D){a.x / b.x, a.y / b.y});
}

/*
-	Multiply two int vector.
*/
t_vector2D mult_2d(t_vector2D a, t_vector2D b)
{
	return ((t_vector2D){a.x * b.x, a.y * b.y});
}

