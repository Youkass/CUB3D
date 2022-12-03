/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:53:48 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 20:45:05 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

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
	t_list	*tmp;
	t_data	*img;

	tmp = _lstimg();
	img = _img();
	(void)tmp;
	img->img = mlx_new_image(_mlx()->mlx, WIN_W, WIN_H);
	if (!img->img)
		ft_black_hole(139);
	ft_lstadd_back(&tmp, ft_new_node(img->img));
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel),
			&(img->line_length), &(img->endian));
	img->bits_per_pixel /= 8;
	img->h = WIN_H;
	img->w = WIN_W;
}

void	ft_pixel_put(float x, float y, int color)
{
	t_data	*img;
	char	*dst;

	img = _img();
	if (x < 0 || y < 0 || x > WIN_W - 1 || y > WIN_H)
		return ;
	dst = img->addr + (int)(y * img->line_length + x
			* (img->bits_per_pixel / 8));
	*(int *)dst = color;
}

void	ft_reload_frame(void)
{
	void	*addr;

	addr = mlx_get_data_addr(_img()->img, &(_img()->bits_per_pixel),
			&(_img()->line_length), &(_img()->endian));
	_img()->addr = addr;
}

void	ft_fps(void)
{
	_var()->old_time = _var()->time;
	_var()->time = get_clock(_var()->clock);
	_var()->frame_time = (get_clock(_var()->clock) - _var()->old_time)
	/ 1000000.0;
	if (_var()->key[ctrl])
		_player()->move_speed = _var()->frame_time * 5.0;
	else
		_player()->move_speed = _var()->frame_time * 3.0;
	_player()->rot_speed = _var()->frame_time * 2.0;
}

void	check_death(void)
{
	if (_player()->health <= 0 && _player()->is_dead == 0)
	{
		_player()->is_dead = 1;
		_player()->deaths++;
		_player()->death_start = get_clock(_var()->clock);
		_player()->death_n = 0;
	}
}
