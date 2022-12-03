/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_array_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:08:29 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 19:08:46 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	arr_fill(t_array *a, int value)
{
	size_t	i;

	i = 0;
	while (i < a->size)
		a->array[i++] = value;
	a->n = 0;
}

void	print_arr(t_array *a)
{
	size_t	i;

	i = 0;
	printf("-----\n");
	while (i <= a->n)
		printf("-> %d\n", a->array[i++]);
	printf("-----\n");
}

int	ft_in_array(t_array *a, int value)
{
	int	i;

	i = 0;
	while (i < (int)a->n)
	{
		if (value == a->array[i])
			return (1);
		i++;
	}
	return (0);
}

t_vector2F	get_90_angle(int dir)
{
	double		deg;
	double		rad;
	t_vector2F	v;

	deg = rad_to_deg(atan2(_player()->dy, _player()->dx)) + (90 * dir);
	rad = deg_to_rad(deg);
	v.x = (cos(rad));
	v.y = (sin(rad));
	v.x += _player()->dx;
	v.y += _player()->dy;
	deg = (atan2(v.y - _player()->dy, v.x - _player()->dx));
	return (posf(cos(deg), sin(deg)));
}
