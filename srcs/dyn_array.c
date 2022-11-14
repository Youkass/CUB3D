/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:12:11 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/14 11:59:50 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_array(t_array *a, int size)
{
	a->n = 0;
	a->size = size;
	a->array = ft_malloc(sizeof(int) * size);
}

int	kill_push(int	value)
{
	_player()->kill_round[_player()->nr++] = value;
	_player()->kill_match[_player()->nm++] = value;
	printf("=>>> %d\n", _player()->nm);
	return (1);
}

int	arr_push(t_array *a, int	value)
{
	if (a->n >= a->size)
		return (0);
	a->array[a->n++] = value;
	return (1);
}

void	arr_pop(t_array *a, int	id)
{
	size_t	i;
	int	poped;

	i = 0;
	poped = 0;
	printf("pop : n = %zu\n", a->n);
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