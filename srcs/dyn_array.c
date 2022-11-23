/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:12:11 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/23 14:00:12 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_array(t_array *a, int size)
{
	a->n = 0;
	a->size = size;
	a->array = ft_malloc(sizeof(int) * size);
}

int	kill_push(int value)
{
	_player()->kill_round[_player()->nr++] = value;
	_player()->kill_match[_player()->nm++] = value;
	return (1);
}

int	arr_push(t_array *a, int value)
{
	if (a->n >= a->size)
		return (0);
	a->array[a->n++] = value;
	return (1);
}

void	arr_pop(t_array *a, int id)
{
	size_t	i;
	int		poped;

	i = 0;
	poped = 0;
	while (i < a->n)
	{
		if (a->array[i] == id)
		{
			++poped;
			break ;
		}
		i++;
	}
	while (i + 1 < a->n)
	{
		a->array[i] = a->array[i + 1];
		i++;
	}
	if (poped && a->n > 0)
		a->n--;
}

void	arr_destroy(t_array *a)
{
	free(a->array);
	free(a);
}

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
	(void)a;
	(void)i;
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
