/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:32:57 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/09 19:35:05 by denissereno      ###   ########.fr       */
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

unsigned long	get_time(unsigned long start)
{
	return (get_clock(_var()->clock) - start);
}

unsigned long	get_time_server(unsigned long start, struct timeval clock)
{
	return (get_clock(clock) - start);
}