/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:53:48 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:24:16 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

/*
===============================================================================
The following function will initialize our mlx pointer and our mlx window
===============================================================================
*/
void	ft_init_mlx(void)
{
	void	*win;

	_mlx()->mlx = mlx_init();
	if (!_mlx()->mlx)
	{
		free(_mlx());
		exit(0);
	}
	win = mlx_new_window(_mlx()->mlx, WIN_W, WIN_H, PRG_NAME);
	if (!win)
	{
		mlx_destroy_display(_mlx()->mlx);
		free(_mlx()->mlx);
		free(_mlx());
		exit(0);
	}
	_mlx()->mlx_win = win;
}
