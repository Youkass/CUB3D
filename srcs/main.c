/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:32:59 by yobougre          #+#    #+#             */
/*   Updated: 2022/11/16 19:39:03 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> 
# include "../includes/cub.h"

void	get_key(int keycode)
{
	if (keycode == CTRL)
		_var()->key[ctrl] = 1;
	if (keycode == A_)
		_var()->key[a] = 1;
	if (keycode == W)
		_var()->key[w] = 1;
	if (keycode == S_)
		_var()->key[s] = 1;
	if (keycode == D)
		_var()->key[d] = 1;
	if (keycode == ONE)
		_var()->key[one] = 1;
	if (keycode == TWO)
		_var()->key[two] = 1;
	if (keycode == THREE)
		_var()->key[three] = 1;
	if (keycode == F)
		_var()->key[f] = 1;
	if (keycode == ESC)
		_var()->key[esc] = 1;
	if (keycode == ARR_UP)
		_var()->key[up] = 1;
	if (keycode == ARR_DOWN)
		_var()->key[down] = 1;
	if (keycode == ARR_LEFT)
		_var()->key[left] = 1;
	if (keycode == ARR_RIGHT)
		_var()->key[right] = 1;
	if (keycode == SPACE)
		_var()->key[space] = 1;
	if (keycode == MAJ)
		_var()->key[maj] = 1;
	if (keycode == R)
		_var()->key[r] = 1;
}

int	ft_release(int keycode)
{
	if (keycode == A_)
	{
		_var()->key[a] = 0;
		_player()->is_walking = 0;
	}
	if (keycode == CTRL)
		_var()->key[ctrl] = 0;
	if (keycode == W)
	{
		_var()->key[w] = 0;
		_player()->is_walking = 0;
	}
	if (keycode == S_)
	{
		_var()->key[s] = 0;
		_player()->is_walking = 0;
	}
	if (keycode == D)
	{
		_var()->key[d] = 0;
		_player()->is_walking = 0;
	}
	if (keycode == ESC)
		_var()->key[esc] = 0;
	if (keycode == ARR_UP)
		_var()->key[up] = 0;
	if (keycode == ARR_DOWN)
		_var()->key[down] = 0;
	if (keycode == ARR_LEFT)
		_var()->key[left] = 0;
	if (keycode == ARR_RIGHT)
		_var()->key[right] = 0;
	if (keycode == SPACE)
		_var()->key[space] = 0;
	if (keycode == MAJ)
		_var()->key[maj] = 0;
	if (keycode == R)
		_var()->key[r] = 0;
	if (keycode == ONE)
		_var()->key[one] = 0;
	if (keycode == TWO)
		_var()->key[two] = 0;
	if (keycode == THREE)
		_var()->key[three] = 0;
	if (keycode == F)
		_var()->key[f] = 0;
	return (0);
}

void	generate_dsprite(void)
{
	_image()->dsprite[0] = generate_image("./img/soldier/new_blue/front.xpm"); // front
	_image()->dsprite[1] = generate_image("./img/soldier/new_blue/front_east_1.xpm"); // front east
	_image()->dsprite[2] = generate_image("./img/soldier/new_blue/front_east_2.xpm"); // front east
	_image()->dsprite[3] = generate_image("./img/soldier/new_blue/front_east_3.xpm"); // front east
	_image()->dsprite[4] = generate_image("./img/soldier/new_blue/east.xpm"); // east
	_image()->dsprite[5] = generate_image("./img/soldier/new_blue/back_east_1.xpm"); // back east
	_image()->dsprite[6] = generate_image("./img/soldier/new_blue/back_east_2.xpm"); // back east
	_image()->dsprite[7] = generate_image("./img/soldier/new_blue/back_east_3.xpm"); // back east
	_image()->dsprite[8] = generate_image("./img/soldier/new_blue/back.xpm"); // back
	_image()->dsprite[9] = generate_image("./img/soldier/new_blue/back_west_3.xpm"); // back west
	_image()->dsprite[10] = generate_image("./img/soldier/new_blue/back_west_2.xpm"); // back west
	_image()->dsprite[11] = generate_image("./img/soldier/new_blue/back_west_1.xpm"); // back west
	_image()->dsprite[12] = generate_image("./img/soldier/new_blue/west.xpm"); // west
	_image()->dsprite[13] = generate_image("./img/soldier/new_blue/front_west_3.xpm"); // front west
	_image()->dsprite[14] = generate_image("./img/soldier/new_blue/front_west_2.xpm"); // front west
	_image()->dsprite[15] = generate_image("./img/soldier/new_blue/front_west_1.xpm"); // front westwest

	_image()->walk_sprite[0] = generate_image("./img/soldier/new_blue/walk/front.xpm");
	_image()->walk_sprite[1] = generate_image("./img/soldier/new_blue/walk/southeast.xpm");
	_image()->walk_sprite[2] = generate_image("./img/soldier/new_blue/walk/east.xpm");
	_image()->walk_sprite[3] = generate_image("./img/soldier/new_blue/walk/northeast.xpm");
	_image()->walk_sprite[4] = generate_image("./img/soldier/new_blue/walk/back.xpm");
	_image()->walk_sprite[5] = generate_image("./img/soldier/new_blue/walk/northwest.xpm");
	_image()->walk_sprite[6] = generate_image("./img/soldier/new_blue/walk/west.xpm");
	_image()->walk_sprite[7] = generate_image("./img/soldier/new_blue/walk/southwest.xpm");

	_image()->death_sprite = generate_image("./img/soldier/new_blue/death.xpm");

	_image()->rifle = generate_image("./img/soldier/rifle.xpm");
}

void	generate_dsprite_red(void)
{
	_image()->dsprite_red[0] = generate_image("./img/soldier/red/front.xpm"); // front
	_image()->dsprite_red[1] = generate_image("./img/soldier/red/front_east_1.xpm"); // front east
	_image()->dsprite_red[2] = generate_image("./img/soldier/red/front_east_2.xpm"); // front east
	_image()->dsprite_red[3] = generate_image("./img/soldier/red/front_east_3.xpm"); // front east
	_image()->dsprite_red[4] = generate_image("./img/soldier/red/east.xpm"); // east
	_image()->dsprite_red[5] = generate_image("./img/soldier/red/back_east_1.xpm"); // back east
	_image()->dsprite_red[6] = generate_image("./img/soldier/red/back_east_2.xpm"); // back east
	_image()->dsprite_red[7] = generate_image("./img/soldier/red/back_east_3.xpm"); // back east
	_image()->dsprite_red[8] = generate_image("./img/soldier/red/back.xpm"); // back
	_image()->dsprite_red[9] = generate_image("./img/soldier/red/back_west_3.xpm"); // back west
	_image()->dsprite_red[10] = generate_image("./img/soldier/red/back_west_2.xpm"); // back west
	_image()->dsprite_red[11] = generate_image("./img/soldier/red/back_west_1.xpm"); // back west
	_image()->dsprite_red[12] = generate_image("./img/soldier/red/west.xpm"); // west
	_image()->dsprite_red[13] = generate_image("./img/soldier/red/front_west_3.xpm"); // front west
	_image()->dsprite_red[14] = generate_image("./img/soldier/red/front_west_2.xpm"); // front west
	_image()->dsprite_red[15] = generate_image("./img/soldier/red/front_west_1.xpm"); // front westwest

	_image()->walk_sprite_red[0] = generate_image("./img/soldier/red/walk/front.xpm");
	_image()->walk_sprite_red[1] = generate_image("./img/soldier/red/walk/southeast.xpm");
	_image()->walk_sprite_red[2] = generate_image("./img/soldier/red/walk/east.xpm");
	_image()->walk_sprite_red[3] = generate_image("./img/soldier/red/walk/northeast.xpm");
	_image()->walk_sprite_red[4] = generate_image("./img/soldier/red/walk/back.xpm");
	_image()->walk_sprite_red[5] = generate_image("./img/soldier/red/walk/northwest.xpm");
	_image()->walk_sprite_red[6] = generate_image("./img/soldier/red/walk/west.xpm");
	_image()->walk_sprite_red[7] = generate_image("./img/soldier/red/walk/southwest.xpm");

	_image()->death_sprite_red = generate_image("./img/soldier/red/death.xpm");
}

void	restart_player(void)
{
	double	dist;
	int		i;

	_player()->is_start = 0;
	_log()->log = NULL;
	_var()->alive[TRED] = _var()->nb_player / 2;
	_var()->alive[TBLUE] = _var()->nb_player / 2;
	memset(&_player()->kill_match, 0, sizeof(_player()->kill_match));
	memset(&_player()->kill_round, 0, sizeof(_player()->kill_round));
	_player()->nr = 0;
	_var()->match_finished = 0;
	_player()->kills = 0;
	_player()->deaths = 0;
	memset(_player()->kill_round, 0, sizeof(_player()->kill_round));
	_player()->nr = 0;
	_player()->nm = 0;
	_player()->is_shooting = 0;
	_player()->can_shoot = 1;
	_player()->start_reload = get_clock(_var()->clock);
	_player()->health = 100;
	i = 0;
	while (i < NB_WEAPONS)
	{
		_player()->ammo[i] = _weapon()[i]->ammo;
		_player()->full_ammo[i] = _weapon()[i]->full_ammo;
		i++;
	}
	_player()->shoot_n = 0;
	_player()->z = 0;
	_player()->dx = -1;
	_player()->shooted.id = -1;
	_player()->shooted.shoot = 0;
	_player()->dy = 0;
	_player()->is_dead = 0;
	_player()->is_crouching = 0;
	_player()->death_n = 0;
	_player()->plane = (t_vector2F){0, -0.66};
	_player()->pitch = 0;
	_player()->norm_pitch = 0;
	dist = hypot(_player()->dx, _player()->dy);
	_player()->angle = 360 - acos(_player()->dx / dist) * 180 / M_PI;
	_player()->is_walking = 0;
	_player()->spectate = 0;
	_player()->spec_id = -1;
}

void	ft_init_player_pos(void)
{
	double	dist;
	int		i;

	_player()->team = TEAM_VOID;
	memset(_var()->blue, 0, sizeof(_var()->blue));
	memset(_var()->red, 0, sizeof(_var()->red));
	memset(_var()->neutral, 0, sizeof(_var()->neutral));
	memset(&_player()->kill_match, 0, sizeof(_player()->kill_match));
	memset(&_player()->kill_round, 0, sizeof(_player()->kill_round));
	_player()->nr = 0;
	_player()->nm = 0;
	_var()->n_blue = 0;
	_log()->log = NULL;
	_player()->spectate = 0;
	_player()->spec_id = -1;
	_var()->n_red = 0;
	_var()->n_neutral = 0;
	_player()->pseudo[0] = 0;
	_player()->is_shooting = 0;
	_player()->exchange = 4;
	_player()->weapon_id = 0;
	_player()->can_shoot = 1;
	_player()->start_reload = get_clock(_var()->clock);
	_player()->health = 100;
	i = 0;
	while (i < NB_WEAPONS)
	{
		_player()->ammo[i] = _weapon()[i]->ammo;
		_player()->full_ammo[i] = _weapon()[i]->full_ammo;
		i++;
	}
	_player()->shoot_n = 0;
	_player()->x = 5;
	_player()->y = 3;
	_player()->change_team = -1;
	_player()->z = 0;
	_player()->scale = 0.8;
	_player()->dx = -1;
	_player()->shooted.id = -1;
	_player()->shooted.shoot = 0;
	_player()->dy = 0;
	_player()->is_crouching = 0;
	_player()->is_dead = 0;
	_player()->death_n = 0;
	_player()->plane = (t_vector2F){0, -0.66};
	_var()->time = 0;
	_var()->old_time = 0;
	_player()->hb.hit.r = 0.5;
	_player()->hb.n = 0;
	_player()->pitch = 0;
	_player()->norm_pitch = 0;
	generate_dsprite();
	generate_dsprite_red();
	_image()->sprite = generate_image("./img/front.xpm");
	dist = hypot(_player()->dx, _player()->dy);
	_player()->angle = 360 - acos(_player()->dx / dist) * 180 / M_PI;
	_player()->is_walking = 0;
	init_data_shot(_player());
	_player()->is_start = 0;
}

void	walk_clock(void)
{
	if (get_clock(_var()->clock) - _var()->walk_start > 50000 )
	{
		_var()->walk_n++;
		if (_var()->walk_n >= 16)
			_var()->walk_n = 0;
		_var()->walk_start = get_clock(_var()->clock);
	}
}

void	death_clock(void)
{
	if (_player()->death_n == 15 || _player()->is_dead != 1)
		return ;
	if (get_clock(_var()->clock) - _player()->death_start > 50000 )
	{
		_player()->death_n++;
		if (_player()->death_n >= 16)
			_player()->death_n = 15;
		_player()->death_start = get_clock(_var()->clock);
	}
}

void	reload_clock(void)
{
	if (get_clock(_var()->clock) - _player()->start_reload > _weapon()[_player()->weapon_id]->reload_ms)
	{
		_player()->can_shoot = 1;
		_player()->is_shooting = 0;
	}
}

void	ft_init_player2(void)
{
	double	dist;
	int		i;

	i = 0;
	while (i < MAX_PLAYER)
	{
		_image()->pseudo_img[i].img = NULL;
		_var()->o_player[i].weapon_id = 0;
			_var()->o_player[i].team = 0;
		_var()->o_player[i].health = 100;
		_var()->o_player[i].x = 7;
		_var()->o_player[i].y = 8;
		_var()->o_player[i].z = 20;
		_var()->o_player[i].is_walking = 0;
		_var()->o_player[i].dx = -1;
		_var()->o_player[i].dy = 0;
		_var()->o_player[i].plane = (t_vector2F){0, -0.66};
		_var()->o_player[i].hb.hit.r = 0.5;
		_var()->o_player[i].hb.n = 0;
		_var()->o_player[i].shoot_n = 0;
		dist = hypot(_var()->o_player[i].dx, _var()->o_player[i].dy);
		_var()->o_player[i].angle = 360 - acos(_var()->o_player[i].dx / dist) * 180 / M_PI;	
		init_data_shot(&_var()->o_player[i]);
		++i;
	}
}


void	ft_print_tab(char **s)
{
	int	i;
	int	line;

	i = 0;
	while (s[i])
	{
		printf("%s\n", s[i]);
		line = ft_strlen(s[i]);
		++i;
	}
	_var()->map_width = line;
	_var()->map_height = i;
}

int	ft_hook(int keycode)
{
	get_key(keycode);
	//if (_var()->mode == GAME)
	//	ft_game_hook(keycode);
	if (_var()->mode == MENU)
		menu_hook(keycode);
	if (_var()->mode == MENU && _menu()->mode == MENU_PSEUDO)
	{
		menu_hook_pseudo(keycode);
	}
	if (_var()->mode == MENU && _menu()->mode == MENU_IP)
		menu_hook_ip(keycode);
	return (0);
}

int	ft_mouse_hook(int keycode)
{
	if (_var()->mode == MENU)
		menu_mouse_hook(keycode);
	return (0);
}

int	ft_loop_hook(void)
{
	int	pid;

	if (_var()->mode == ONLINE_START)
	{
			_var()->is_host = SERVER;
			pid = fork();
			if (pid == 0)
			{
				system(ft_strjoin("./server ", ft_itoa(_var()->nb_player)));
				ft_black_hole(1);
			}
			else
			{
				sleep(1);
				if (ft_init_client() == EXIT_FAILURE)
					_menu()->mode = MENU_START;
			}
		_var()->mode = LOBBY_WAIT;
	}
	ft_fps();
	key_hook();
	if (_var()->mode == GAME_START_ONLINE)
	{
		init_teams();
		_var()->mode = GAME;
	}
	if (_var()->mode == GAME)
	{
		ft_loop();
		// mlx_mouse_hide(_mlx()->mlx, _mlx()->mlx_win);
		// mouse_rotate();
	}
	if (_var()->mode == MENU || _var()->mode == LOBBY_WAIT)
		menu_loop();

	return (0);
}

int	ft_mouse_release(int keycode)
{
	if (keycode == 1)
		_var()->key[mouse] = 0;
	return (0);
}

int	ft_expose(void *data)
{
	int	*mode;

	mode = (int *)data;
	if (*mode == GAME)
	{
		mlx_mouse_hide(_mlx()->mlx, _mlx()->mlx_win);
		mlx_mouse_move(_mlx()->mlx, _mlx()->mlx_win, WIN_W / 2, WIN_H / 2);
	}
	return (0);
}

int	ft_rotate(double rot_speed)
{
	double	dist;

	_player()->old_dx = _player()->dx;
	_player()->dx = _player()->dx * cos(rot_speed)
	- _player()->dy * sin(rot_speed);
	_player()->dy = _player()->old_dx * sin(rot_speed)
	+ _player()->dy * cos(rot_speed);
	_player()->old_plane.x = _player()->plane.x;
	_player()->plane.x = _player()->plane.x * cos(rot_speed)
	- _player()->plane.y * sin(rot_speed);
	_player()->plane.y = _player()->old_plane.x * sin(rot_speed)
	+ _player()->plane.y * cos(rot_speed);
	dist = hypot(_player()->dx, _player()->dy);
	if (_player()->dy <= 0)
		_player()->angle = acos(_player()->dx / dist) * 180 / M_PI;
	else
		_player()->angle = 360 - acos(_player()->dx / dist) * 180 / M_PI;
	return (0);
}

int	mouse_rotate(void)
{
	t_vector2D	pos;
	t_vector2D	delta;

	mlx_mouse_get_pos(_mlx()->mlx, _mlx()->mlx_win, &pos.x, &pos.y);
	delta.x = pos.x - WIN_W / 2;
	delta.y = (pos.y - WIN_H / 2) * 25;
	ft_rotate(delta.x * _var()->frame_time * SENSIBILITY);
	_player()->pitch -= delta.y * _player()->move_speed;
	if(_player()->pitch > 500)
		_player()->pitch = 500;
	_player()->norm_pitch = normalise_between2F(posf(-1000, 1000),
		posf(-1, 1), _player()->pitch);
	mlx_mouse_move(_mlx()->mlx, _mlx()->mlx_win, WIN_W / 2, WIN_H / 2);
	return (0);
}

int	ft_game(void)
{
	mlx_hook(_mlx()->mlx_win, 2, 1L << 0, &ft_hook, NULL);
	mlx_hook(_mlx()->mlx_win, 3, 1L << 1, &ft_release, NULL);
	mlx_loop_hook(_mlx()->mlx, &ft_loop_hook, NULL);
	mlx_hook(_mlx()->mlx_win, 5, 1L << 3, &ft_mouse_release, NULL);
	mlx_mouse_hook(_mlx()->mlx_win, &menu_mouse_hook, NULL);
	// mlx_expose_hook(_mlx()->mlx_win, ft_expose, &_var()->mode);
	return (0);
}

void	init_key(void)
{
	_var()->key[a] = 0;
	_var()->key[b] = 0;
	_var()->key[c] = 0;
	_var()->key[d] = 0;
	_var()->key[e] = 0;
	_var()->key[f] = 0;
	_var()->key[g] = 0;
	_var()->key[h] = 0;
	_var()->key[i] = 0;
	_var()->key[j] = 0;
	_var()->key[k] = 0;
	_var()->key[l] = 0;
	_var()->key[m] = 0;
	_var()->key[n] = 0;
	_var()->key[o] = 0;
	_var()->key[p] = 0;
	_var()->key[q] = 0;
	_var()->key[r] = 0;
	_var()->key[s] = 0;
	_var()->key[t] = 0;
	_var()->key[u] = 0;
	_var()->key[v] = 0;
	_var()->key[w] = 0;
	_var()->key[x] = 0;
	_var()->key[y] = 0;
	_var()->key[z] = 0;
	_var()->key[one] = 0;
	_var()->key[two] = 0;
	_var()->key[three] = 0;
	_var()->key[four] = 0;
	_var()->key[five] = 0;
	_var()->key[six] = 0;
	_var()->key[seven] = 0;
	_var()->key[eight] = 0;
	_var()->key[nine] = 0;
	_var()->key[zero] = 0;
	_var()->key[underscore] = 0;
	_var()->key[esc] = 0;
	_var()->key[mouse] = 0;
	_var()->key[up] = 0;
	_var()->key[down] = 0;
	_var()->key[left] = 0;
	_var()->key[right] = 0;
	_var()->key[space] = 0;
	_var()->key[ctrl] = 0;
	_var()->key[maj] = 0;
}

void	init_var(void)
{
	int	i;
	
	memset(_var(), 0, sizeof(t_var));
	if (pthread_mutex_init(&_log()->mutex, NULL))
		ft_black_hole(137);
	_var()->mode = MENU;
	_menu()->mode = MENU_START;
	_var()->walk_n = 0;
	_var()->clock = start_clock();
	_var()->walk_start = get_clock(_var()->clock);
	_var()->team_start = 0;
	_var()->team_match = 0;
	_var()->freeze = 0;
	init_teams();
	_var()->last_round_winner = -1;
	//_image()->bullet = generate_image("./img/bullet.xpm");
	i = 0;
	while (i < MAX_PLAYER)
		_image()->pseudo_img[i++].img = NULL;
	_var()->started = 0;
	_var()->start_click = 0;
	_var()->click = 0;
	_var()->click_keycode = 0;
	_var()->reload_anim = 0;
	_var()->shot_anim = 0;
	_var()->shotanim_start = get_clock(_var()->clock);
	_var()->reloadanim_start = get_clock(_var()->clock);
}

void	init_data_shot(t_obj *player)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < MAX_BULLET)
	{
		player->shott[i].end_pos = (t_vector2F){0, 0};
		player->shott[i].n = 0;
		while (j < SHOT_FRAME)
		{
			player->shott[i].n_pos[j] = (t_vector2F){0, 0};
			j++;
		}
		player->shott[i].pos = (t_vector2F){0, 0};
		player->shott[i].shot = 0;
		player->shott[i].start_pos = (t_vector2F){0, 0};
		player->shott[i].start_time = 0;
		player->shott[i].weapon_type = 0;
		i++;
	}
}

//int	is_wall(char c)
//{
//	if (c != 0 || c != 'P')
//		return (1);
//	return (0);
//}

void	init_image(void)
{
	_image()->bullet = generate_image("./img/bullet.xpm");
	_image()->ammo = generate_image("./img/ammo.xpm");
	_image()->crosshair = generate_image("./img/crosshair.xpm");
	_image()->front = generate_image("./img/soldier/front.xpm");
	if(WIN_W == 1440)
		_image()->bg = generate_image("./img/spacebg1440.xpm");
	else
		_image()->bg = generate_image("./img/spacebg.xpm");
	_image()->weapons[0][NORMAL] = ft_malloc(sizeof(t_data));
	_image()->weapons[0][NORMAL][0] = generate_image("./img/weapons/rifle/rifle.xpm");
	_image()->weapons[0][ATTACK] = ft_malloc(sizeof(t_data) * 3);
	_image()->weapons[0][ATTACK][0] = generate_image("./img/weapons/rifle/rifleshoot1.xpm");
	_image()->weapons[0][ATTACK][1] = generate_image("./img/weapons/rifle/rifleshoot2.xpm");
	_image()->weapons[0][ATTACK][2] = generate_image("./img/weapons/rifle/rifleshoot3.xpm");
	_image()->weapons[0][RELOAD] = ft_malloc(sizeof(t_data) * 8);
	_image()->weapons[0][RELOAD][0] = generate_image("./img/weapons/rifle/riflereload1.xpm");
	_image()->weapons[0][RELOAD][1] = generate_image("./img/weapons/rifle/riflereload2.xpm");
	_image()->weapons[0][RELOAD][2] = generate_image("./img/weapons/rifle/riflereload3.xpm");
	_image()->weapons[0][RELOAD][3] = generate_image("./img/weapons/rifle/riflereload4.xpm");
	_image()->weapons[0][RELOAD][4] = generate_image("./img/weapons/rifle/riflereload5.xpm");
	_image()->weapons[0][RELOAD][5] = generate_image("./img/weapons/rifle/riflereload6.xpm");
	_image()->weapons[0][RELOAD][6] = generate_image("./img/weapons/rifle/riflereload7.xpm");
	_image()->weapons[0][RELOAD][7] = generate_image("./img/weapons/rifle/riflereload8.xpm");

	_image()->weapons[1][NORMAL] = ft_malloc(sizeof(t_data));
	_image()->weapons[1][NORMAL][0] = generate_image("./img/weapons/gun/gun.xpm");
	_image()->weapons[1][ATTACK] = ft_malloc(sizeof(t_data) * 6);
	_image()->weapons[1][ATTACK][0] = generate_image("./img/weapons/gun/gunshot1.xpm");
	_image()->weapons[1][ATTACK][1] = generate_image("./img/weapons/gun/gunshot2.xpm");
	_image()->weapons[1][ATTACK][2] = generate_image("./img/weapons/gun/gunshot3.xpm");
	_image()->weapons[1][ATTACK][3] = generate_image("./img/weapons/gun/gunshot4.xpm");
	_image()->weapons[1][ATTACK][4] = generate_image("./img/weapons/gun/gunshot5.xpm");
	_image()->weapons[1][ATTACK][5] = generate_image("./img/weapons/gun/gunshot6.xpm");
	_image()->weapons[1][RELOAD] = ft_malloc(sizeof(t_data) * 4);
	_image()->weapons[1][RELOAD][0] = generate_image("./img/weapons/gun/gunreload1.xpm");
	_image()->weapons[1][RELOAD][1] = generate_image("./img/weapons/gun/gunreload2.xpm");
	_image()->weapons[1][RELOAD][2] = generate_image("./img/weapons/gun/gunreload3.xpm");
	_image()->weapons[1][RELOAD][3] = generate_image("./img/weapons/gun/gunreload4.xpm");

	_image()->weapons[2][NORMAL] = ft_malloc(sizeof(t_data));
	_image()->weapons[2][NORMAL][0] = generate_image("./img/weapons/knife/knife.xpm");
	_image()->weapons[2][ATTACK] = ft_malloc(sizeof(t_data));
	_image()->weapons[2][ATTACK][0] = generate_image("./img/weapons/knife/knifeattack.xpm");
	_image()->weapons[2][RELOAD] = NULL;
}

int main(int argc, char **argv)
{
	int		fd;

	(void)argc;
	init_var();
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_black_hole(139);
	_var()->map = resize_map(ft_split(read_file(fd), '\n'));
	if (!_var()->map)
		ft_black_hole(139);
	init_weapons();
	ft_print_tab(_var()->map);
	ft_init_mlx();
	ft_init_media();
	ft_init_img();
	_ray();
	ft_init_player_pos();
	ft_init_player2();
	ft_malloc_map();
	init_key();
	_menu()->n_ip = 0;
	gen_menu_images();
	init_image();
	ft_game();
	mlx_loop(_mlx()->mlx);
	return (0);
}
