/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */ /*   mlx_utils.c                                        :+:      :+:    :+:   */ /*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:29:30 by yobougre          #+#    #+#             */
/*   Updated: 2022/11/12 12:34:41 by yobougre         ###   ########.fr       */
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
	_img()->h = WIN_H;
	_img()->w = WIN_W;
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
	// mlx_destroy_images(_mlx()->mlx, _img()->img);
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
	_player()->move_speed = _var()->frame_time * 3.0;
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
//					ft_put_pixel(_img(), &_image()->bg, (t_vector2D){var.i, var.j}, (t_vector2D){xo, (var.j + WIN_H / 2) - _player()->pitch});
//			}
//			else
//				ft_put_pixel_color(_img(), (char [4]){155, 155, 155, 0}, var.i, var.j);
//			var.j++;
//		}
//		var.i++;
//	}
//	if (planet[0].x != -1 && planet[0].y != -1)
//		ft_put_sprite_to_images(*_img(), _menu()->planets[0],  planet[0], (t_vector2D){_menu()->n * 48, _menu()->ny * 48},  (t_vector2D){48, 48});
//	if (planet[1].x != -1 && planet[1].y != -1)
//		ft_put_sprite_to_images(*_img(), _menu()->planets[0],  planet[1], (t_vector2D){_menu()->n * 48, _menu()->ny * 48},  (t_vector2D){48, 48});
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
					_menu()->planets_pos[0] = (t_vector2D){xo, var.j};
				else if (var.i == 200 && (var.j + WIN_H / 2) - _player()->pitch == 200)
					_menu()->planets_pos[1] = (t_vector2D){xo, var.j};
				else
					ft_put_pixel(_img(), &_image()->bg, (t_vector2D){var.i, var.j}, (t_vector2D){xo, (var.j + WIN_H / 2) - _player()->pitch});
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
		//		ft_put_pixel(_img(), &_menu()->bg, (t_vector2D){(int)var.i, (int)var.j}, (t_vector2D){(int)var.i, (int)var.j});
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
	int			pitch;
	static t_vector2D	pl_coord[2] = (t_vector2D [2]){{2000, 500}, {1050, 500}};
	_menu()->draw_pl[0] = pos(-1, -1);
	_menu()->draw_pl[1] = pos(-1, -1);

	if (_player()->spectate && _player()->spec_id >= 0 && _player()->spec_id <= 
	_var()->linked_players)
	{
		angle = atan2(_var()->o_player[_player()->spec_id].dy,
			_var()->o_player[_player()->spec_id].dx);
		pitch = _var()->o_player[_player()->spec_id].pitch;
	}
	else
	{
		angle = atan2(_player()->dy, _player()->dx);
		pitch = _player()->pitch;
	}
	offset = (int)(angle * WIN_W* 2 / (M_PI * 2)) + (WIN_W / 2) * 2;
	pt.y = 0;
	while (pt.y < WIN_H / 2 + pitch)
	{
		tex.y =( ((pt.y * 2 * WIN_W / (WIN_H)) / 4 )- (pitch * 0.8)) + WIN_H / 2;
		pt.x = 0;
		while (pt.x < WIN_W)
		{
			tex.x = pt.x * WIN_W / (4 * WIN_W / 2);
			if (tex.x + offset == pl_coord[0].x && tex.y == 400)
				_menu()->draw_pl[0] = (t_vector2D){pt.x, pt.y};
			tex.x = (tex.x + offset) % WIN_W;
			ft_put_pixel(_img(), &_image()->bg, pt, tex);
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
	if ( _menu()->draw_pl[0].x != -1 &&  _menu()->draw_pl[0].y != -1)
		ft_put_sprite_to_images(*_img(), _menu()->planets[0], _menu()->draw_pl[0], (t_vector2D){_menu()->n * 48, _menu()->ny * 48},  (t_vector2D){48, 48});
}

void	draw_void_thread()
{
	static t_vector2D	r[10];
	static int			started = 0;

	_menu()->planets_pos[0] = (t_vector2D){-1, -1};
	_menu()->planets_pos[1] = (t_vector2D){-1, -1};
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
	if ( _menu()->planets_pos[0].x != -1 &&  _menu()->planets_pos[0].y != -1)
		ft_put_sprite_to_images(*_img(), _menu()->planets[0], _menu()->planets_pos[0], (t_vector2D){_menu()->n * 48, _menu()->ny * 48},  (t_vector2D){48, 48});
	if ( _menu()->planets_pos[1].x != -1 &&  _menu()->planets_pos[1].y != -1)
		ft_put_sprite_to_images(*_img(), _menu()->planets[0], _menu()->planets_pos[1], (t_vector2D){_menu()->n * 48, _menu()->ny * 48},  (t_vector2D){48, 48});
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
	int	i;
	int	new_shoot_n;
	t_vector2F velo;

	new_shoot_n = _player()->shoot_n;
	i = 0;
	while (i < _player()->shoot_n)
	{
		_player()->shott[i].n++;
		velo = velocity_get_point(_player()->shott[i].start_pos, _player()->shott[i].velo.velo, get_time(_player()->shott[i].start_time));
		if (get_time(_player()->shott[i].start_time) >= (float)_player()->shott[i].velo.time_ms)
			new_shoot_n--;
		else
			_player()->shott[i].pos = velo;
		i++;
	}
	_player()->shoot_n = new_shoot_n;
}

void	recompute_array_shot(int index)
{
	while (index + 1 < _player()->shoot_n)
	{
		_player()->shott[index] = _player()->shott[index + 1];
		index++;
	}
}

void	update_bullets3F(void)
{
	int	i;
	int	new_shoot_n;
	t_vector3F velo;

	new_shoot_n = _player()->shoot_n;
	i = 0;
	while (i < _player()->shoot_n)
	{
		//if (_player()->shott[i].n == 0)
			//_player()->shott[i].start_time = get_clock(_var()->clock);
		_player()->shott[i].n++;
		velo = velocity_get_point3F(_player()->shott[i].start_pos3F, _player()->shott[i].velo3.velo, get_time(_player()->shott[i].start_time));
		if (get_time(_player()->shott[i].start_time) >= (float)_player()->shott[i].velo3.time_ms)
		{
			new_shoot_n--;
			recompute_array_shot(i);
		}
		else
			_player()->shott[i].pos3F = velo;
		i++;
	}
	_player()->shoot_n = new_shoot_n;
}


void	hud(void)
{
	ft_put_image_to_image(*_img(), _image()->crosshair, pos(WIN_W / 2 - 8,
		WIN_H / 2 - 8));
	if (_player()->is_shooting)
	{
		ft_put_sprite_to_images(*_img(), _image()->rifle,
					pos(WIN_W / 2 - (_image()->rifle.w / 4),
					WIN_H - _image()->rifle.h), pos(_image()->rifle.w / 2, 0),
					pos(_image()->rifle.w / 2, _image()->rifle.h));
	}
	else
	{
		ft_put_sprite_to_images(*_img(), _image()->rifle,
			pos(WIN_W / 2 - (_image()->rifle.w / 4), WIN_H - _image()->rifle.h),
			pos(0, 0), pos(_image()->rifle.w / 2, _image()->rifle.h));
	}	
}

void	set_spectate(void)
{
	int	i;

	i = 0;
	if (_player()->is_dead && _var()->red_alive > 0 && _var()->blue_alive > 0)
	{
		_player()->spectate = 1;
		_player()->spec_id = - 1;
		while (i < _var()->nb_player)
		{
			if (_var()->o_player[i].team == _player()->team
				&& _var()->o_player[i].is_dead == 0)
				_player()->spec_id = i;
			i++;
		}
	}
}

int	ft_loop()
{
	planet_clock();
	draw_sky();
	check_death();
	death_clock();
	reload_clock();
	draw_rays();
	walk_clock();
//	ft_play_music(0, GAME_MUSIC);
	set_spectate();
//	if (_player()->is_shooting > 0)
//		ft_play_sound(_player()->id);
	printf("%d, %d\n", _var()->mode, _menu()->mode);
	if ((_var()->is_host == CLIENT || _var()->is_host == SERVER))
	{
		ft_pong_client();
		player_casting();
		name_casting();
		char *str;
		if (_player()->team == TEAM_RED)
			str = ft_strjoin(ft_itoa(_team()[TEAM_RED]->win), ft_strjoin(" - ", ft_itoa(_team()[TEAM_BLUE]->win)));
		else
			str = ft_strjoin(ft_itoa(_team()[TEAM_BLUE]->win), ft_strjoin(" - ", ft_itoa(_team()[TEAM_RED]->win)));
		draw_text_scale(str, pos(WIN_W / 2 - (ft_strlen(str) * (42)) / 2, 100), pos(1, 1), WHITE);
	}
	update_bullets3F();
	bullet_casting();
	hud();
	if (_var()->round_state == ROUND_END_WAIT)
	{
		if (_var()->last_round_winner == TRED)
			draw_text_scale("RED WIN THE ROUND", pos(WIN_W / 2 - (17 * (42)) / 2, 300), pos(1, 1), RED);
		else if (_var()->last_round_winner == TBLUE)
			draw_text_scale("BLUE WIN THE ROUND", pos(WIN_W / 2 - (18 * (42)) / 2, 300), pos(1, 1), BLUE);
		else
			draw_text_scale(ft_itoa(_var()->last_round_winner), pos(WIN_W / 2 - (1 * (42)) / 2, 300), pos(1, 1), BLUE);
	}
	ft_draw_map();
	draw_text_scale(ft_strjoin(ft_itoa(_player()->full_ammo), "/"), pos(WIN_W - _image()->ammo.w - 90, WIN_H - _image()->ammo.h - 10), pos(3, 3), WHITE);
	draw_text_scale(ft_itoa(_player()->ammo), pos(WIN_W - _image()->ammo.w - 90 + ft_strlen("45/") * 14, WIN_H - _image()->ammo.h - 8), pos(3, 3), WHITE);
	ft_put_image_to_image_scale(*_img(), _image()->ammo, pos(WIN_W - _image()->ammo.w - 20, WIN_H - _image()->ammo.h - 10), posf(4, 4));//
	mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win, _img()->img, 0, 0);
	ft_reload_frame();
	return (0);
}
