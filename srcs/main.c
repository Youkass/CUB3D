/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:32:59 by yobougre          #+#    #+#             */
/*   Updated: 2022/11/09 15:53:06 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"
#include <unistd.h> 
/*int main(int argc, char** argv)
{
    ma_result result;
    ma_engine engine;

    if (argc < 2) {
        printf("No input file.");
        return -1;
    }

    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        printf("Failed to initialize audio engine.");
        return -1;
    }

    ma_engine_play_sound(&engine, argv[1], NULL);

    printf("Press Enter to quit...");
    getchar();

    ma_engine_uninit(&engine);

    return 0;
}
*/
void	ft_init_media(void)
{
	_media()->result = ma_engine_init(NULL, &(_media()->engine));
	if (_media()->result != MA_SUCCESS)
		exit (1); //TODO
	_media()->result = ma_sound_init_from_file(&(_media()->engine),
		"sound/test_sound.wav", 0, NULL, NULL, &(_media()->sound[0]));
	if (_media()->result != MA_SUCCESS)
		exit (1); //TODO
	_media()->result = ma_sound_init_from_file(&(_media()->engine),
		"sound/menu_music.wav", 0, NULL, NULL, &(_media()->sound[MENU_MUSIC]));
	if (_media()->result != MA_SUCCESS)
		exit (1); //TODO
	_media()->result = ma_sound_init_from_file(&(_media()->engine),
		"sound/game_music.wav", 0, NULL, NULL, &(_media()->sound[GAME_MUSIC]));
	if (_media()->result != MA_SUCCESS)
		exit (1); //TODO
}

void	ft_play_music(long unsigned int time, int index)
{
	static long	start = 0;

	if (!start)
	{
		ma_sound_start(&(_media()->sound[index]));
		start = get_clock(_var()->clock);
	}
	(void)time;
	if (_var()->mode == GAME)
	{
		ma_sound_stop(&(_media()->sound[MENU_MUSIC]));
		start = 0;
	}
}


void	get_key(int keycode)
{
	if (keycode == A_)
		_var()->key.a = 1;
	if (keycode == W)
		_var()->key.w = 1;
	if (keycode == S_)
		_var()->key.s = 1;
	if (keycode == D)
		_var()->key[d] = 1;
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
}

int	ft_release(int keycode)
{
	if (keycode == A_)
		_var()->key.a = 0;
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
		_var()->key[d] = 0;
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
	return (0);
}

void	generate_dsprite(void)
{
	_image()->dsprite[0] = generate_image("./img/soldier/front.xpm"); // front
	_image()->dsprite[1] = generate_image("./img/soldier/front_east_1.xpm"); // front east
	_image()->dsprite[2] = generate_image("./img/soldier/front_east_2.xpm"); // front east
	_image()->dsprite[3] = generate_image("./img/soldier/front_east_3.xpm"); // front east
	_image()->dsprite[4] = generate_image("./img/soldier/east.xpm"); // east
	_image()->dsprite[5] = generate_image("./img/soldier/back_east_1.xpm"); // back east
	_image()->dsprite[6] = generate_image("./img/soldier/back_east_2.xpm"); // back east
	_image()->dsprite[7] = generate_image("./img/soldier/back_east_3.xpm"); // back east
	_image()->dsprite[8] = generate_image("./img/soldier/back.xpm"); // back
	_image()->dsprite[9] = generate_image("./img/soldier/back_west_3.xpm"); // back west
	_image()->dsprite[10] = generate_image("./img/soldier/back_west_2.xpm"); // back west
	_image()->dsprite[11] = generate_image("./img/soldier/back_west_1.xpm"); // back west
	_image()->dsprite[12] = generate_image("./img/soldier/west.xpm"); // west
	_image()->dsprite[13] = generate_image("./img/soldier/front_west_3.xpm"); // front west
	_image()->dsprite[14] = generate_image("./img/soldier/front_west_2.xpm"); // front west
	_image()->dsprite[15] = generate_image("./img/soldier/front_west_1.xpm"); // front westwest

	_image()->walk_sprite[0] = generate_image("./img/soldier/walk/front.xpm");
	_image()->walk_sprite[1] = generate_image("./img/soldier/walk/southeast.xpm");
	_image()->walk_sprite[2] = generate_image("./img/soldier/walk/east.xpm");
	_image()->walk_sprite[3] = generate_image("./img/soldier/walk/northeast.xpm");
	_image()->walk_sprite[4] = generate_image("./img/soldier/walk/back.xpm");
	_image()->walk_sprite[5] = generate_image("./img/soldier/walk/northwest.xpm");
	_image()->walk_sprite[6] = generate_image("./img/soldier/walk/west.xpm");
	_image()->walk_sprite[7] = generate_image("./img/soldier/walk/southwest.xpm");

	_image()->death_sprite = generate_image("./img/soldier/death.xpm");

	_image()->rifle = generate_image("./img/soldier/rifle.xpm");
}


void	ft_init_player_pos(void)
{
	double	dist;

	_player()->team = TEAM_VOID;
	memset(_var()->blue, 0, sizeof(_var()->blue));
	memset(_var()->red, 0, sizeof(_var()->red));
	memset(_var()->neutral, 0, sizeof(_var()->neutral));
	_var()->n_blue = 0;
	_var()->n_red = 0;
	_var()->n_neutral = 0;
	_player()->pseudo[0] = 0;
	_player()->is_shooting = 0;
	_player()->exchange = 4;
	_player()->weapon_id = 0;
	_player()->can_shoot = 1;
	_player()->start_reload = get_clock(_var()->clock);
	_player()->health = 100;
	_player()->ammo = 0;
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
		menu_hook_pseudo(keycode);
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
				sleep(1);
				ft_init_client();
				printf("je suis dans loop_hook\n");
			}
			else
			{
				system(ft_strjoin("./server ", ft_itoa(_var()->nb_player)));
				exit(1);
			}
		_var()->mode = LOBBY_WAIT;
	}
	ft_fps();
	key_hook();
	if (_var()->mode == GAME)
		ft_loop();
	else if (_var()->mode == MENU || _var()->mode == LOBBY_WAIT)
		menu_loop();

	return (0);
}

int	ft_mouse_release(int keycode)
{
	if (keycode == 1)
		_var()->key[mouse] = 0;
	return (0);
}

int	ft_game(void)
{
	mlx_hook(_mlx()->mlx_win, 2, 1L << 0, &ft_hook, NULL);
	mlx_hook(_mlx()->mlx_win, 3, 1L << 1, &ft_release, NULL);
	mlx_loop_hook(_mlx()->mlx, &ft_loop_hook, NULL);
	mlx_hook(_mlx()->mlx_win, 5, 1L << 3, &ft_mouse_release, NULL);
	mlx_mouse_hook(_mlx()->mlx_win, &menu_mouse_hook, NULL);
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
}

void	init_weapons(void)
{
	_weapon()[0]->name = malloc(sizeof(char) * 6);
	_weapon()[0]->name = "Rifle\0";
	_weapon()[0]->id = 0;
	_weapon()[0]->range = 25;
	_weapon()[0]->power = 25;
	_weapon()[0]->reload_ms = 500000;
	_weapon()[0]->ammo = 15;
	_weapon()[0]->headshot = 50;
	_weapon()[0]->footshot = 10;
}

void	init_var(void)
{
	int	i;

	_var()->mode = MENU;
	_menu()->mode = MENU_START;_var()->walk_n = 0;
	_var()->clock = start_clock();
	_var()->walk_start = get_clock(_var()->clock);
	//_image()->bullet = generate_image("./img/bullet.xpm");
	i = 0;
	while (i < MAX_PLAYER)
		_image()->pseudo_img[i++].img = NULL;
	_var()->started = 0;
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

void	init_teams(void)
{
	int			i;
	
	_team()[TRED]->loose = 0;
	_team()[TRED]->win = 0;
	_team()[TRED]->team_spawn = posf(3, 3);
	i = 0;
	while (i < _var()->nb_player / 2)
	{
		_team()[TRED]->players[i] = _var()->red[i];
		i++;
	}
	_team()[TRED]->player_spawn[0] = posf(3, 3);
	_team()[TRED]->player_spawn[1] = posf(3, 4);
	_team()[TRED]->player_spawn[2] = posf(3, 2);

	_team()[TBLUE]->loose = 0;
	_team()[TBLUE]->win = 0;
	_team()[TBLUE]->team_spawn = posf(40, 9);
	i = 0;
	while (i < _var()->nb_player / 2)
	{
		_team()[TBLUE]->players[i] = _var()->blue[i];
		i++;
	}
	_team()[TBLUE]->player_spawn[0] = posf(40, 9);
	_team()[TBLUE]->player_spawn[1] = posf(40, 10);
	_team()[TBLUE]->player_spawn[2] = posf(41, 9);
}

int main(int argc, char **argv)
{
	int		fd;

	(void)argc;
	init_var();
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit(139);
	_var()->map = resize_map(ft_split(read_file(fd), '\n'));
	if (!_var()->map)
		exit(139);
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
	gen_menu_images();
	_image()->bullet = generate_image("./img/bullet.xpm");
	_image()->crosshair = generate_image("./img/crosshair.xpm");
	_image()->front = generate_image("./img/soldier/front.xpm");
	if(WIN_W == 1440)
		_image()->bg = generate_image("./img/spacebg1440.xpm");
	else
		_image()->bg = generate_image("./img/spacebg.xpm");
	ft_game();
	mlx_loop(_mlx()->mlx);
	return (0);
}
