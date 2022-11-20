/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:29:30 by yobougre          #+#    #+#             */
/*   Updated: 2022/11/20 21:54:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/*
===============================================================================
The following function will initialize our mlx pointer and our mlx window
===============================================================================
*/
void	ft_init_mlx()
{
	_mlx()->mlx = mlx_init();
	_mlx()->mlx_win = mlx_new_window(_mlx()->mlx, WIN_W, WIN_H, PRG_NAME);
}

/*
===============================================================================
The following function will initialize our frames inside the window
    if (argc != 2)
    {
        printf("Arguments error\n");
        return (1);
    }
===============================================================================
*/
void	ft_init_img()
{
	_img()->img = mlx_new_image(_mlx()->mlx, WIN_W, WIN_H);
	_img()->addr = mlx_get_data_addr(_img()->img, &(_img()->bits_per_pixel),
		&(_img()->line_length), &(_img()->endian));
	_img()->bits_per_pixel /= 8;
//	mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win, _img()->img, 0, 0);
}

/*
===============================================================================
As you can see, if you followed the @Harm_smits tutorial, our pixel put function
is quite different, in our pixel_put function you can see a condition that will
prevent any segmentation fault that could  occure if you tried to put a pixel
outside the window.
-> this function will be call by other functions before pushing the image into the window
===============================================================================
*/
void	ft_pixel_put(float x, float y, int color)
{
	t_data	*img;
	char	*dst;

	img = _img();
	if (x < 0 || y < 0 || x > WIN_W - 1 || y > WIN_H)
		return ;
	dst = img->addr + (int)(y * img->line_length + x * 
		(img->bits_per_pixel / 8)); 
	*(unsigned int*)dst = color;
}

void	ft_put_pixel(t_data *a, t_data *b, t_vector2D pos_a, t_vector2D pos_b)
{
	if (b->addr[((pos_b.y *b->line_length) + (pos_b.x * 4)) + 3] != -1)
	{
		a->addr[pos_a.y * a->line_length + pos_a.x * 4] = b->addr[(pos_b.y *b->line_length)  + (pos_b.x * 4)];
		a->addr[(pos_a.y * a->line_length + pos_a.x * 4) + 1] = b->addr[((pos_b.y *b->line_length)  + (pos_b.x * 4)) + 1];
		a->addr[(pos_a.y * a->line_length + pos_a.x * 4) + 2] = b->addr[((pos_b.y *b->line_length)  + (pos_b.x * 4)) + 2];
		a->addr[(pos_a.y * a->line_length + pos_a.x * 4) + 3] = b->addr[((pos_b.y *b->line_length)  + (pos_b.x * 4)) + 3];
	}
}

void	ft_reload_frame()
{
	mlx_destroy_image(_mlx()->mlx, _img()->img);
	_img()->img = mlx_new_image(_mlx()->mlx, WIN_W, WIN_H);
	_img()->addr = mlx_get_data_addr(_img()->img, &(_img()->bits_per_pixel),
		&(_img()->line_length), &(_img()->endian));
//	_img()->bits_per_pixel /= 8;
	//mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win, _img()->img, 0, 0);
}

void	ft_fps(void)
{
	_ray()->old_time = _ray()->time;
	_ray()->time = get_clock(_ray()->clock);
	_ray()->frame_time = (get_clock(_ray()->clock) - _ray()->old_time) / 1000000.0;
	_player()->move_speed = _ray()->frame_time * 5.0;
	_player()->rot_speed = _ray()->frame_time * 3.0;
}

int	ft_loop()
{
	draw_void();
	draw_rays();
	mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win, _img()->img, 0, 0);
	ft_reload_frame();
	return (0);
}
