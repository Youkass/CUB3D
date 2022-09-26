/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:29:30 by yobougre          #+#    #+#             */
/*   Updated: 2022/09/26 15:59:29 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/*
The following function will initialize our mlx pointer and our mlx window
*/
void	ft_init_mlx(t_mlx *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIN_W, WIN_H, PRG_NAME)
}

/*
The following function will initialize our first image inside the window
*/
void	ft_init_img(t_mlx *data, t_data *img)
{
	img->img = mlx_new_image(mlx, WIN_W, WIN_H);
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel),
		&(img->line_length), &(img->endian));
}

/*
As you can see, if you followed the @Harm_smits tutorial, our pixel put function
is quite different, in our pixel_put function you can see a condition that will
prevent any segmentation fault that could  occure if you tried to put a pixel
outside the window
*/
void	ft_pixel_put(t_data *img, float x, float y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > WIN_W - 1 || y > WIN_H)
		return ;
	dst = data->addr + (y * img->line_length + x * 
		(data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
