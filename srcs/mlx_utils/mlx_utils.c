/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:29:30 by yobougre          #+#    #+#             */
/*   Updated: 2022/11/01 10:39:22 by yobougre         ###   ########.fr       */
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
//	t_vector2D	*planet;

//	planet = (t_vector2D[2]){{-1, -1}, {-1, -1}};
//	var.i = 0;
//	while (var.i < WIN_W)
//	{
//		var.j = 0;
//		while (var.j < WIN_H)
//		{
//			int xo = ((int)_player()->angle * 4) - var.i;
//			if (xo < 0)
//				xo += WIN_W;
//			xo = xo % WIN_W;

//			if (var.j < WIN_H / 2 + _player()->pitch)
//			{
//				if (var.i == 800 && (var.j + WIN_H / 2) - _player()->pitch == 550)
//					planet[0] = (t_vector2D){xo, var.j};
//				else if (var.i == 200 && (var.j + WIN_H / 2) - _player()->pitch == 200)
//					planet[1] = (t_vector2D){xo, var.j};
//				else
//					ft_put_pixel(_img(), &_var()->bg, (t_vector2D){var.i, var.j}, (t_vector2D){xo, (var.j + WIN_H / 2) - _player()->pitch});
//			}
//			else
//				ft_put_pixel_color(_img(), (char [4]){155, 155, 155, 0}, var.i, var.j);
//			var.j++;
//		}
//		var.i++;
//	}
//	if (planet[0].x != -1 && planet[0].y != -1)
//		ft_put_sprite_to_image(*_img(), _var()->menu->planets[0],  planet[0], (t_vector2D){_var()->menu->n * 48, _var()->menu->ny * 48},  (t_vector2D){48, 48});
//	if (planet[1].x != -1 && planet[1].y != -1)
//		ft_put_sprite_to_image(*_img(), _var()->menu->planets[0],  planet[1], (t_vector2D){_var()->menu->n * 48, _var()->menu->ny * 48},  (t_vector2D){48, 48});
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
			int xo = ((int)_player()->angle * 4) - var.i;
			if (xo < 0)
				xo += WIN_W;
			xo = xo % WIN_W;

			if (var.j < WIN_H / 2 + _player()->pitch)
			{
				if (var.i == 800 && (var.j + WIN_H / 2) - _player()->pitch == 550)
					_var()->menu->planets_pos[0] = (t_vector2D){xo, var.j};
				else if (var.i == 200 && (var.j + WIN_H / 2) - _player()->pitch == 200)
					_var()->menu->planets_pos[1] = (t_vector2D){xo, var.j};
				else
					ft_put_pixel(_img(), &_var()->bg, (t_vector2D){var.i, var.j}, (t_vector2D){xo, (var.j + WIN_H / 2) - _player()->pitch});
			}
			else
				ft_put_pixel_color(_img(), (char [4]){155, 155, 155, 0}, var.i, var.j);
			var.j++;
		}
		var.i++;
		//var.j = 0;
		//while (var.j < WIN_H)
		//{
		//	if (var.j < (WIN_H / 2) + _player()->pitch)
		//		ft_put_pixel(_img(), &_var()->menu->bg, (t_vector2D){(int)var.i, (int)var.j}, (t_vector2D){(int)var.i, (int)var.j});
		//	else
		//		ft_put_pixel_color(_img(), (char [4]){50, 168, 82, 0}, (int)var.i, (int)var.j);
		//	var.j++;
		//}
		//var.i++;
	}
	
	return (NULL);
}

void		draw_sky(void)
{
	double		angle;
	int			offset;
	t_vector2D	tex;
	t_vector2D	pt;
	static t_vector2D	pl_coord[2] = (t_vector2D [2]){{2000, 500}, {1050, 500}};
	t_vector2D	draw_pl[2] = {{-1, -1}, {-1, -1}};

	(void)draw_pl;
	angle = atan2(_player()->dy, _player()->dx);
	offset = (int)(angle * WIN_W* 2 / (M_PI * 2)) + (WIN_W / 2) * 2;
	//printf("%d\n", offset);
	pt.y = 0;
	while (pt.y < WIN_H / 2 + _player()->pitch)
	{
		tex.y =( ((pt.y * 2 * WIN_W / (WIN_H)) / 4 )- (_player()->pitch * 0.8)) + WIN_H / 2;
		printf("%d\n", tex.y);
		pt.x = 0;
		while (pt.x < WIN_W)
		{
			tex.x = pt.x * WIN_W / (4 * WIN_W / 2);
			if (tex.x + offset == pl_coord[0].x && tex.y == 400)
				draw_pl[0] = (t_vector2D){pt.x, pt.y};
			tex.x = (tex.x + offset) % WIN_W;
			ft_put_pixel(_img(), &_var()->bg, pt, tex);
			pt.x++;
		}
		pt.y++;
	}
	while (pt.y < WIN_H)
	{
		pt.x = 0;
		while (pt.x < WIN_W)
		{
			ft_put_pixel_color(_img(), (char [4]){250, 144, 144, 0}, pt.x, pt.y);
			pt.x++;
		}
		pt.y++;
	}
	if ( draw_pl[0].x != -1 &&  draw_pl[0].y != -1)
		ft_put_sprite_to_image(*_img(), _var()->menu->planets[0], draw_pl[0], (t_vector2D){_var()->menu->n * 48, _var()->menu->ny * 48},  (t_vector2D){48, 48});
	//if ( _var()->menu->planets_pos[0].x != -1 &&  _var()->menu->planets_pos[0].y != -1)
		//ft_put_sprite_to_image(*_img(), _var()->menu->planets[0], _var()->menu->planets_pos[0], (t_vector2D){_var()->menu->n * 48, _var()->menu->ny * 48},  (t_vector2D){48, 48});
	//if ( _var()->menu->planets_pos[1].x != -1 &&  _var()->menu->planets_pos[1].y != -1)
	//	ft_put_sprite_to_image(*_img(), _var()->menu->planets[0], _var()->menu->planets_pos[1], (t_vector2D){_var()->menu->n * 48, _var()->menu->ny * 48},  (t_vector2D){48, 48});
}

void	draw_void_thread()
{
	static t_vector2D	r[10];
	static int			started = 0;

	_var()->menu->planets_pos[0] = (t_vector2D){-1, -1};
	_var()->menu->planets_pos[1] = (t_vector2D){-1, -1};
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
	if ( _var()->menu->planets_pos[0].x != -1 &&  _var()->menu->planets_pos[0].y != -1)
		ft_put_sprite_to_image(*_img(), _var()->menu->planets[0], _var()->menu->planets_pos[0], (t_vector2D){_var()->menu->n * 48, _var()->menu->ny * 48},  (t_vector2D){48, 48});
	if ( _var()->menu->planets_pos[1].x != -1 &&  _var()->menu->planets_pos[1].y != -1)
		ft_put_sprite_to_image(*_img(), _var()->menu->planets[0], _var()->menu->planets_pos[1], (t_vector2D){_var()->menu->n * 48, _var()->menu->ny * 48},  (t_vector2D){48, 48});
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

void	update_bullets(void)
{
	if (_var()->shott.shot == 1)
	{
		_var()->shott.n++;
		if (_var()->shott.n > 5)
		{
			_var()->shott.shot = 0;
			return ;
		}
		_var()->shott.pos = _var()->shott.n_pos[_var()->shott.n];
	}
}

int	ft_loop()
{
	planet_clock();
	//draw_void_thread();
	draw_sky();
	//ft_draw_void();
	check_death();
	death_clock();
	reload_clock();
	draw_rays();
	walk_clock();
	if ((_img()->is_host == CLIENT || _img()->is_host == SERVER)  && _var()->mode == GAME)
	{
		ft_pong_client();
		player_casting();
		name_casting();
		bullet_casting();
		update_bullets();
	}
	ft_draw_map();
	mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win, _img()->img, 0, 0);
	ft_reload_frame();
	return (0);
}
