/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:01:34 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

void	init_var(void)
{
	memset(_var(), 0, sizeof(t_var));
	if (pthread_mutex_init(&_log()->mutex, NULL))
		ft_black_hole(137);
	memset(&_var()->map, 0, sizeof(_var()->map));
	_var()->mode = MENU;
	_menu()->mode = INTRO;
	_var()->linked_players = 1;
	_var()->walk_n = 0;
	_var()->clock = start_clock();
	_var()->walk_start = get_clock(_var()->clock);
	_var()->team_start = 0;
	_var()->team_match = 0;
	_var()->freeze = 0;
	_var()->tex_mode = 0;
	_var()->tex_dir = 0;
	_var()->walk_tex = 0;
	init_teams();
	_var()->last_round_winner = -1;
	_var()->nx = 0;
	_var()->ny = 0;
	ft_init_var_next();
}

void	init_data_shot(t_obj *player)
{
	int	i;

	i = 0;
	while (i < MAX_BULLET)
	{
		player->shott[i].end_pos = pos3f(0, 0, 0);
		player->shott[i].n = 0;
		player->shott[i].pos = pos3f(0, 0, 0);
		player->shott[i].shot = 0;
		player->shott[i].start_pos = pos3f(0, 0, 0);
		player->shott[i].start_time = 0;
		player->shott[i].weapon_type = 0;
		i++;
	}
}

static void	ft_init_image_next_one(void)
{
	_image()->weapons[0][RELOAD][1] = generate_image(
		"./img/weapons/rifle/riflereload2.xpm");
	_image()->weapons[0][RELOAD][2] = generate_image(
		"./img/weapons/rifle/riflereload3.xpm");
	_image()->weapons[0][RELOAD][3] = generate_image(
		"./img/weapons/rifle/riflereload4.xpm");
	_image()->weapons[0][RELOAD][4] = generate_image(
		"./img/weapons/rifle/riflereload5.xpm");
	_image()->weapons[0][RELOAD][5] = generate_image(
		"./img/weapons/rifle/riflereload6.xpm");
	_image()->weapons[0][RELOAD][6] = generate_image(
		"./img/weapons/rifle/riflereload7.xpm");
	_image()->weapons[0][RELOAD][7] = generate_image(
		"./img/weapons/rifle/riflereload8.xpm");
	_image()->weapons[1][NORMAL] = ft_malloc(sizeof(t_data));
	_image()->weapons[1][NORMAL][0] = generate_image(
		"./img/weapons/gun/gun.xpm");
	_image()->weapons[1][ATTACK] = ft_malloc(sizeof(t_data) * 6);
	_image()->weapons[1][ATTACK][0] = generate_image(
		"./img/weapons/gun/gunshot1.xpm");
	_image()->weapons[1][ATTACK][1] = generate_image(
		"./img/weapons/gun/gunshot2.xpm");
	_image()->weapons[1][ATTACK][2] = generate_image(
		"./img/weapons/gun/gunshot3.xpm");
}

static void	ft_init_image_next_two(void)
{
	_image()->weapons[1][ATTACK][3] = generate_image(
		"./img/weapons/gun/gunshot4.xpm");
	_image()->weapons[0][RELOAD][0] = generate_image(
		"./img/weapons/rifle/riflereload1.xpm");
	_image()->weapons[1][ATTACK][4] = generate_image(
		"./img/weapons/gun/gunshot5.xpm");
	_image()->weapons[1][ATTACK][5] = generate_image(
		"./img/weapons/gun/gunshot6.xpm");
	_image()->weapons[1][RELOAD] = ft_malloc(sizeof(t_data) * 4);
	_image()->weapons[1][RELOAD][0] = generate_image(
		"./img/weapons/gun/gunreload1.xpm");
	_image()->weapons[1][RELOAD][1] = generate_image(
		"./img/weapons/gun/gunreload2.xpm");
	_image()->weapons[1][RELOAD][2] = generate_image(
		"./img/weapons/gun/gunreload3.xpm");
	_image()->weapons[1][RELOAD][3] = generate_image(
		"./img/weapons/gun/gunreload4.xpm");
	_image()->weapons[2][NORMAL] = ft_malloc(sizeof(t_data));
	_image()->weapons[2][NORMAL][0] = generate_image(
		"./img/weapons/knife/knife.xpm");
	_image()->weapons[2][ATTACK] = ft_malloc(sizeof(t_data));
	_image()->weapons[2][ATTACK][0] = generate_image(
		"./img/weapons/knife/knifeattack.xpm");
	_image()->weapons[2][RELOAD] = NULL;
}

void	init_image(void)
{
	_image()->bullet = generate_image("./img/bullet.xpm");
	_image()->ammo = generate_image("./img/ammo.xpm");
	_image()->crosshair = generate_image("./img/crosshair.xpm");
	_image()->hitmarker = generate_image("./img/hitmarker.xpm");
	_image()->front = generate_image("./img/soldier/front.xpm");
	if (WIN_W == 1440)
		_image()->bg = generate_image("./img/spacebg1440.xpm");
	else
		_image()->bg = generate_image("./img/spacebg.xpm");
	_image()->weapons[0][NORMAL] = ft_malloc(sizeof(t_data));
	_image()->weapons[0][NORMAL][0] = generate_image(
		"./img/weapons/rifle/rifle.xpm");
	_image()->weapons[0][ATTACK] = ft_malloc(sizeof(t_data) * 3);
	_image()->weapons[0][ATTACK][0] = generate_image(
		"./img/weapons/rifle/rifleshoot1.xpm");
	_image()->weapons[0][ATTACK][1] = generate_image(
		"./img/weapons/rifle/rifleshoot2.xpm");
	_image()->weapons[0][ATTACK][2] = generate_image(
		"./img/weapons/rifle/rifleshoot3.xpm");
	_image()->weapons[0][RELOAD] = ft_malloc(sizeof(t_data) * 8);
	ft_init_image_next_one();
	ft_init_image_next_two();
}
