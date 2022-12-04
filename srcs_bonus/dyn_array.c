/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:12:11 by denissereno       #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub.h"

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
