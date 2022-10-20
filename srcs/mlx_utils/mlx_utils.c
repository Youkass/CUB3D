/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:29:30 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/19 21:02:08 by denissereno      ###   ########.fr       */
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
	_img()->height = WIN_H;
	_img()->width = WIN_W;
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
	*( int*)dst = color;
}

void	ft_reload_frame()
{
	// mlx_destroy_image(_mlx()->mlx, _img()->img);
	// _img()->img = mlx_new_image(_mlx()->mlx, WIN_W, WIN_H);
	_img()->addr = mlx_get_data_addr(_img()->img, &(_img()->bits_per_pixel),
		&(_img()->line_length), &(_img()->endian));
//	_img()->bits_per_pixel /= 8;
	//mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win, _img()->img, 0, 0);
}

void	ft_fps(void)
{
	_var()->old_time = _var()->time;
	_var()->time = get_clock(_var()->clock);
	_var()->frame_time = (get_clock(_var()->clock) - _var()->old_time) / 1000000.0;
	//printf("FPS = %d\n",  (int)(1.0 / _var()->frame_time));ft_
	_player()->move_speed = _var()->frame_time * 5.0;
	_player()->rot_speed = _var()->frame_time * 2.0;
}

//void	ft_draw_void()
//{
//	t_int	var;

//	var.i = 0;
//	while (var.i < WIN_W)
//	{
//		var.j = 0;
//		while (var.j < WIN_H)
//		{
//			if (var.j < WIN_H / 2)
//				ft_pixel_put(var.i, var.j, 0xD3D3D3);
//			else
//				ft_pixel_put(var.i, var.j, 0x32a852);
//			var.j++;
//		}
//		var.i++;
//	}
//}

void	*ft_draw_void(void *r)
{
	t_int		var;
	t_vector2D	start_end;

	start_end = *(t_vector2D *)r;
	var.i = start_end.x;
	while (var.i < start_end.y)
	{
		var.j = 0;
		while (var.j < WIN_H)
		{
			if (var.j < (WIN_H / 2) + _player()->pitch)
				ft_put_pixel_color(_img(), (char [4]){211, 211, 211, 0}, (int)var.i, (int)var.j);
			else
				ft_put_pixel_color(_img(), (char [4]){50, 168, 82, 0}, (int)var.i, (int)var.j);
			var.j++;
		}
		var.i++;
	}
	return (NULL);
}

void	draw_void_thread()
{
	static t_vector2D	r[10];
	static int			started = 0;

	if (!started)
	{
		for (int i = 0; i < 10; i++)
			r[i] = (t_vector2D){ (WIN_W / 10) * i, (WIN_W / 10) * (i + 1)};
		started = 1;
	}
	for (int i = 0; i < 10; i++)
		pthread_create(&_var()->th_void[i], NULL, ft_draw_void, &r[i]);
	for (int i = 0; i < 10; i++)
		pthread_join(_var()->th_void[i], NULL);
}

void	check_death(void)
{
	if (_player()->health <= 0 && _player()->is_dead == 0)
	{
		_player()->is_dead = 1;
		_player()->death_start = get_clock(_var()->clock);
		_player()->death_n = 0;
	}
}

int	ft_loop()
{
	draw_void_thread();
	check_death();
	death_clock();
	reload_clock();
	draw_rays();
	walk_clock();
	if (_img()->is_host == CLIENT || _img()->is_host == SERVER)
	{
		ft_pong_client();
		player_casting();
	}
	ft_draw_map();
	ft_put_sprite_to_image(*_img(), _player()->rifle, (t_vector2D){500 , 500}, (t_vector2D){0 , 0}, (t_vector2D){520 , 528});
	mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win, _img()->img, 0, 0);
	ft_reload_frame();
	return (0);
}
