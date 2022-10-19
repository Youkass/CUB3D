/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:32:57 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/19 14:59:22 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

struct timeval	start_clock()
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return (start);
}

unsigned long	get_clock(struct timeval start)
{
	struct timeval	stop;

	gettimeofday(&stop, NULL);
	return ((stop.tv_sec - start.tv_sec) * 1000000
		+ stop.tv_usec - start.tv_usec);
}

void	walk_clock(void)
{
	if (get_clock(_var()->clock) - _var()->walk_start > 50000 )
	{
		_var()->walk_n++;
		if (_var()->walk_n >= 16)
			_var()->walk_n = 0;
		_var()->walk_start = get_clock(_var()->clock);
	}
}
