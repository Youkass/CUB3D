/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:12:11 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/13 16:09:14 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_array(t_array *a, int size)
{
	a->n = 0;
	a->size = size;
	a->array = malloc(sizeof(int) * size);
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
	int	i;
	int	poped;

	i = 0;
	poped = 0;
	printf("pop : n = %zu\n", a->n);
	while (i < (int)a->n)
	{
		if (a->array[i] == id)
		{
			++poped;
			break ;
		}
		i++;
	}
	while (i + 1 < (int)a->n)
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

void	print_tab(t_array *a)
{
	int	i;

	i = 0;
	printf("-----\n");
	while (i <= (int)a->n)
		printf("%d\n", a->array[i++]);
	printf("-----\n");
}
