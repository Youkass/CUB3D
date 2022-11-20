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
	t_list	*tmp;
	t_data	*img;

	tmp = _lstimg();
	img = _img();
	(void)tmp;
	img->img = mlx_new_image(_mlx()->mlx, WIN_W, WIN_H);
	if (!img->img)
		ft_black_hole(139);
	//ft_lstadd_back(&tmp, ft_new_node(&img->img));
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel),
		&(img->line_length), &(img->endian));
	img->bits_per_pixel /= 8;
	img->h = WIN_H;
	img->w = WIN_W;
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
	_img()->addr = mlx_get_data_addr(_img()->img, &(_img()->bits_per_pixel),
		&(_img()->line_length), &(_img()->endian));
}

void	ft_fps(void)
{
	_var()->old_time = _var()->time;
	_var()->time = get_clock(_var()->clock);
	_var()->frame_time = (get_clock(_var()->clock) - _var()->old_time) / 1000000.0;
	if (_var()->key[ctrl])
		_player()->move_speed = _var()->frame_time * 5.0;
	else
		_player()->move_speed = _var()->frame_time * 3.0;
	_player()->rot_speed = _var()->frame_time * 2.0;
}


/*===============================================================================*/
/* DRAW SKY UNDER																 */
/*===============================================================================*/
static void	ft_next_while_draw_sky(t_vector2D pt)
{
	while (pt.y < WIN_H)
	{
		pt.x = 0;
		while (pt.x < WIN_W)
		{
			ft_put_pixel_color_unsigned(_img(), _var()->colors[0],
				pt.x, pt.y);
			pt.x++;
		}
		pt.y++;
	}
	if ( _menu()->draw_pl[0].x != -1 &&  _menu()->draw_pl[0].y != -1)
		ft_put_sprite_to_images(*_img(), _menu()->planets[0],
			_menu()->draw_pl[0], (t_vector2D){_menu()->n * 48,
				_menu()->ny * 48},  (t_vector2D){48, 48});
}

static void	ft_norme_while_draw_sky(int offst, int pitch, t_vector2D *pl_coord)
{
	t_vector2D	pt;
	t_vector2D	tex;

	pt.y = 0;
	while (pt.y < WIN_H / 2 + pitch)
	{
		tex.y = (((pt.y * 2 * WIN_W / (WIN_H)) / 4 )
			- (pitch * 0.8)) + WIN_H / 2;
		pt.x = 0;
		while (pt.x < WIN_W)
		{
			tex.x = pt.x * WIN_W / (4 * WIN_W / 2);
			if (tex.x + offst == pl_coord[0].x && tex.y == 400)
				_menu()->draw_pl[0] = (t_vector2D){pt.x, pt.y};
			tex.x = (tex.x + offst) % WIN_W;
			if (_img() && _image()->bg.img)
				ft_put_pixel(_img(), &_image()->bg, pt, tex);
			pt.x++;
		}
		pt.y++;
	}
	ft_next_while_draw_sky(pt);
}

static void	ft_norme_draw_sky(t_vector2D *pl_coord)
{
	double	angle;
	int		offset;
	int		pitch;

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
	ft_norme_while_draw_sky(offset, pitch, pl_coord);
}

void	draw_sky(void)
{
	static t_vector2D	pl_coord[2] = {{2000, 500}, {1050, 500}};

	_menu()->draw_pl[0] = pos(-1, -1);
	_menu()->draw_pl[1] = pos(-1, -1);
	ft_norme_draw_sky(pl_coord);
}
/*===============================================================================*/
/* DRAW SKY UPSIDE																 */
/*===============================================================================*/

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
	}
	
	return (NULL);
}

void	draw_void_thread(void)
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
		ft_put_sprite_to_images(*_img(),
			_menu()->planets[0], _menu()->planets_pos[0],
				(t_vector2D){_menu()->n * 48,
					_menu()->ny * 48},  (t_vector2D){48, 48});
	if ( _menu()->planets_pos[1].x != -1
			&&  _menu()->planets_pos[1].y != -1)
		ft_put_sprite_to_images(*_img(),
			_menu()->planets[0], _menu()->planets_pos[1],
				(t_vector2D){_menu()->n * 48,
					_menu()->ny * 48}, (t_vector2D){48, 48});
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

void	update_bullets(void)
{
	int	i;
	int	new_shoot_n;
	t_vector3F velo;

	new_shoot_n = _player()->shoot_n;
	i = 0;
	while (i < _player()->shoot_n)
	{
		_player()->shott[i].n++;
		velo = velocity_get_point3F(_player()->shott[i].start_pos,
			_player()->shott[i].velo.velo,
				get_time(_player()->shott[i].start_time));
		if (get_time(_player()->shott[i].start_time)
				>= (float)_player()->shott[i].velo.time_ms)
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
		_player()->shott[i].n++;
		velo = velocity_get_point3F(_player()->shott[i].start_pos,
			_player()->shott[i].velo.velo,
				get_time(_player()->shott[i].start_time));
		if (get_time(_player()->shott[i].start_time)
				>= (float)_player()->shott[i].velo.time_ms)
		{
			new_shoot_n--;
			recompute_array_shot(i);
		}
		else
			_player()->shott[i].pos = velo;
		i++;
	}
	_player()->shoot_n = new_shoot_n;
}

static void	ft_help_hud_if(int index, unsigned long time_attack, int weapon_id)
{
	index = normalise_between(pos(0,
		_weapon()[weapon_id]->reload_ms),
			pos(0,  _weapon()[weapon_id]->shot_frames),
				time_attack);
	if (weapon_id == KNIFE)
		ft_put_image_to_image_scale(*_img(),
			_image()->weapons[weapon_id][ATTACK][0],
				pos(WIN_W / 2 -
					(_image()->weapons
						[weapon_id][ATTACK][0].w * 2 / 4) + 200,
							WIN_H -
								_image()->weapons
									[weapon_id][ATTACK][0].h * 2),
										posf(0.5, 0.5));
	else
		ft_put_image_to_image_scale(*_img(),
			_image()->weapons[weapon_id][ATTACK]
				[index], pos(WIN_W / 2 -
					(_image()->weapons[weapon_id][ATTACK]
						[index].w * 2 / 4) + 200, WIN_H -
							_image()->weapons
								[weapon_id]
									[ATTACK][index].h * 2), posf(0.5, 0.5));
}

static void	ft_help_hud_else_if(int index, unsigned long time_reload,
	int weapon_id)
{
	index = normalise_between(pos(0,
		_weapon()[weapon_id]->anim_reloadms), pos(0,
			_weapon()[weapon_id]->reload_frames), time_reload);
	ft_put_image_to_image_scale(*_img(),
		_image()->weapons[weapon_id][RELOAD]
			[index], pos(WIN_W / 2 -
				(_image()->weapons[weapon_id][RELOAD]
					[index].w * 2 / 4) + 200, WIN_H -
						_image()->weapons[weapon_id][RELOAD]
							[index].h * 2 + 50), posf(0.5, 0.5));
}

static void	ft_help_hud_else(int weapon_id)
{
	_var()->shot_anim = 0;
	_var()->reload_anim = 0;
	ft_put_image_to_image_scale(*_img(),
		_image()->weapons[weapon_id][NORMAL]
			[0], pos(WIN_W / 2 -
				(_image()->weapons[weapon_id][NORMAL]
					[0].w * 2 / 4) + 200, WIN_H - _image()->weapons
						[weapon_id][NORMAL][0].h * 2),
							posf(0.5, 0.5));
}

void	hud_hit_and_touch(void)
{
	if (_player()->touched)
		ft_put_image_to_image(*_img(), _image()->hitmarker, pos(WIN_W / 2 - 8,
			WIN_H / 2 - 8));
	else
		ft_put_image_to_image(*_img(), _image()->crosshair, pos(WIN_W / 2 - 8,
			WIN_H / 2 - 8));
	if (_player()->touched == 1 && get_time(_var()->start_touch) > 100000)
		_player()->touched = 0;

	if (_player()->hitted)
	{
		draw_rectangle(pos(0, 0), pos(WIN_W, 20), RED);
		draw_rectangle(pos(0, WIN_H - 20), pos(WIN_W, 20), RED);
		draw_rectangle(pos(0, 0), pos(20, WIN_H), RED);
		draw_rectangle(pos(WIN_W - 20, 0), pos(20, WIN_H), RED);
	}
	if (_player()->hitted == 1 && get_time(_var()->start_hit) > 100000)
		_player()->hitted = 0;
}

void	hud(void)
{
	unsigned long	time_attack;
	unsigned long	time_reload;
	int				index;
	int				weapon_id;

	time_attack = get_time(_var()->shotanim_start);
	time_reload = get_time(_var()->reloadanim_start);
	index = 0;
	if (_player()->spectate && _player()->spec_id > 0 && _player()->spec_id
	< _var()->linked_players)
		weapon_id = _var()->o_player[_player()->spec_id].weapon_id;
	else
		weapon_id = _player()->weapon_id;
	if (_var()->shot_anim
			&& time_attack < _weapon()[_player()->weapon_id]->reload_ms)
		ft_help_hud_if(index, time_attack, weapon_id);
	else if (_var()->reload_anim
			&& (int)time_reload < _weapon()[_player()->weapon_id]->anim_reloadms)
		ft_help_hud_else_if(index, time_reload, weapon_id);
	else
		ft_help_hud_else(weapon_id);
	hud_hit_and_touch();
	if (_var()->round_state == ROUND_WAIT_START)
		draw_text(ft_itoa(_var()->time_start), pos(WIN_W / 2 - 42, 100),
			WHITE);
}

void	set_spectate(void)
{
	int						i;
	static unsigned long	start = 0;

	i = 0;
	if (!start && _player()->is_dead)
		start = get_clock(_var()->clock);
	if (start && _player()->is_dead && _var()->alive[TRED] > 0
		&& _var()->alive[TBLUE] > 0 && _var()->linked_players > 2
		&& get_time(start) > 300000)
	{
		_player()->spectate = 1;
		_player()->spec_id = - 1;
		while (i < _var()->linked_players)
		{
			if (_var()->o_player[i].team == _player()->team
				&& _var()->o_player[i].is_dead == 0)
				_player()->spec_id = i;
			i++;
		}
	}
}

static void	ft_loop_multi(void)
{
		char *str;

		ft_pong_client();
		player_casting();
		name_casting();
		if (_player()->team == TEAM_RED)
			str = ft_strjoin(ft_itoa(_team()[TEAM_RED]->win),
				ft_strjoin(" - ", ft_itoa(_team()[TEAM_BLUE]->win)));
		else
			str = ft_strjoin(ft_itoa(_team()[TEAM_BLUE]->win),
				ft_strjoin(" - ", ft_itoa(_team()[TEAM_RED]->win)));
		draw_text_scale(str,
			pos(WIN_W / 2 - (ft_strlen(str) * (42)) / 2, 100),
				pos(1, 1), WHITE);
		render_kill_log();
}

static void	ft_if_round_end_wait(void)
{
	if (_var()->last_round_winner == TRED)
		draw_text_scale("RED WIN THE ROUND",
			pos(WIN_W / 2 - (17 * (42)) / 2, 300), pos(1, 1), RED);
	else if (_var()->last_round_winner == TBLUE)
		draw_text_scale("BLUE WIN THE ROUND",
			pos(WIN_W / 2 - (18 * (42)) / 2, 300), pos(1, 1), BLUE);
	else
		draw_text_scale(ft_itoa(_var()->last_round_winner),
			pos(WIN_W / 2 - (1 * (42)) / 2, 300), pos(1, 1), BLUE);
}

static void	ft_call(void)
{
	planet_clock();
	draw_sky();
	check_death();
	death_clock();
	reload_clock();
	draw_rays();
	walk_clock();
	ft_play_music(GAME_MUSIC);
	set_spectate();
}

static void	ft_is_not_knife(void)
{
	draw_text_scale(
		ft_strjoin(ft_itoa(_player()->full_ammo[_player()->weapon_id]),
			"/"), pos(55, 220 + _image()->ammo.h - 10), pos(3, 3), WHITE);
	draw_text_scale(ft_itoa(_player()->ammo[_player()->weapon_id]),
		pos(55 + ft_strlen("45/") * 14,
			220 + _image()->ammo.h - 8), pos(3, 3), WHITE);
	ft_put_image_to_image_scale(*_img(),
		_image()->ammo, pos(125, 220 + _image()->ammo.h - 10), posf(4, 4));
}

void	draw_death(void)
{
	char					*str;

	str = ft_strjoin("Spectating ", _var()->o_player[_player()->
			spec_id].pseudo);
	if (_player()->spectate && _player()->spec_id >= 0 && _player()->spec_id
		<= _var()->linked_players)
		draw_text(str, pos(WIN_W / 2 - ft_strlen(str), WIN_H - 100), WHITE);
	else
		draw_text("You are dead..", pos(WIN_W / 2 - 168, 100), WHITE);
}

int	ft_loop(void)
{
	printf("linked => %d\n", _var()->linked_players);
	ft_call();
	if ((_var()->is_host == CLIENT || _var()->is_host == SERVER))
		ft_loop_multi();
	if (_player()->is_shooting > 0)
		ft_play_own_shot();
	update_bullets3F();
	bullet_casting();
	hud();
	if (_var()->round_state == ROUND_END_WAIT)
		ft_if_round_end_wait();
	ft_draw_map();
	render_health(pos(50, 250));
	if (_player()->weapon_id != KNIFE)
		ft_is_not_knife();
	if (_player()->is_dead)
		draw_death();
	mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win, _img()->img, 0, 0);
	ft_reload_frame();
	return (0);
}
