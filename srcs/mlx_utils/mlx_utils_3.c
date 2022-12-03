/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:53:48 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 16:54:26 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/*
===============================================================================
The following function will initialize our mlx pointer and our mlx window
===============================================================================
*/
void	ft_init_mlx(void)
{
	void	*win;

	_mlx()->mlx = mlx_init();
	win = mlx_new_window(_mlx()->mlx, WIN_W, WIN_H, PRG_NAME);
	_mlx()->mlx_win = win;
}
