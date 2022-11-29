/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:32:57 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/29 18:20:35 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

struct timeval	start_clock(void)
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

void	ft_black_hole(int exit_code)
{
	t_list	*tmp;
	int		i;

	tmp = _lst();
	while (i < 4)
		mlx_destroy_image(_mlx()->mlx, _var()->dir[i++].img);
	mlx_destroy_image(_mlx()->mlx, _img()->img);
	mlx_destroy_window(_mlx()->mlx, _mlx()->mlx_win);
	mlx_destroy_display(_mlx()->mlx);
	free(_mlx()->mlx);
	ft_lstclear(&tmp, free);
	exit(exit_code);
}
