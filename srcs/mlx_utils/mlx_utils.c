/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:29:30 by yobougre          #+#    #+#             */
/*   Updated: 2022/09/26 19:00:23 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/*
The following function will initialize our mlx pointer and our mlx window
*/
void	ft_init_mlx()
{
	t_mlx	*mlx;

	mlx = _mlx();
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, PRG_NAME);
}

/*
The following function will initialize our first image inside the window
*/
void	ft_init_img()
{
	t_mlx	*mlx;
	t_data	*img;

	mlx = _mlx();
	img = _img();
	img->img = mlx_new_image(mlx, WIN_W, WIN_H);
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel),
		&(img->line_length), &(img->endian));
}

/*
As you can see, if you followed the @Harm_smits tutorial, our pixel put function
is quite different, in our pixel_put function you can see a condition that will
prevent any segmentation fault that could  occure if you tried to put a pixel
outside the window.
-> this function will be call by other functions before pushing the image into the window
*/
void	ft_pixel_put(float x, float y, int color)
{
	t_data	*img;

	img = _img();
	if (x < 0 || y < 0 || x > WIN_W - 1 || y > WIN_H)
		return ;
	*(unsigned int *)(img->addr + (int)(y * img->line_length + x * 
		(img->bits_per_pixel / 8))) = color;
}
