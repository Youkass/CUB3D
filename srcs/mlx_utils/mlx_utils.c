/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:29:30 by yobougre          #+#    #+#             */
/*   Updated: 2022/12/04 20:55:34 by dasereno         ###   ########.fr       */
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
void	ft_init_img(void)
{
	char	*tmp;
	void	*img;

	img = mlx_new_image(_mlx()->mlx, WIN_W, WIN_H);
	_img()->img = img;
	if (!_img()->img)
	{
		mlx_destroy_window(_mlx()->mlx, _mlx()->mlx_win);
		mlx_destroy_display(_mlx()->mlx);
		free(_mlx()->mlx);
		free(_mlx());
		exit(0);
	}
	tmp = mlx_get_data_addr(_img()->img, &(_img()->bits_per_pixel),
			&(_img()->line_length), &(_img()->endian));
	_img()->addr = tmp;
	_img()->bits_per_pixel /= 8;
}

// ============================================================================
// As you can see, if you followed the @Harm_smits tutorial, our pixel put fct
// is quite different, in our pixel_put function you can see a condition that
// will prevent any segmentation fault that could  occure if you tried to put a 
// pixel outside the window.
// -> this function will be call by other functions before pushing the image 
//into the window
// ============================================================================

void	ft_reload_frame(void)
{
	char	*tmp;
	void	*img;

	mlx_destroy_image(_mlx()->mlx, _img()->img);
	img = mlx_new_image(_mlx()->mlx, WIN_W, WIN_H);
	_img()->img = img;
	tmp = mlx_get_data_addr(_img()->img, &(_img()->bits_per_pixel),
			&(_img()->line_length), &(_img()->endian));
	_img()->addr = tmp;
}

void	ft_fps(void)
{
	_ray()->old_time = _ray()->time;
	_ray()->time = get_clock(_ray()->clock);
	_ray()->frame_time = (get_clock(_ray()->clock) - _ray()->old_time)
	/ 1000000.0;
	_player()->move_speed = _ray()->frame_time * 5.0;
	_player()->rot_speed = _ray()->frame_time * 3.0;
}

int	ft_loop(void)
{
	draw_void();
	draw_rays();
	mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win, _img()->img, 0, 0);
	ft_reload_frame();
	return (0);
}
