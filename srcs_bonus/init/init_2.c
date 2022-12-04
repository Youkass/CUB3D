/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:01:34 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

static void	ft_init_player_2_values(int i, double dist)
{
	t_vector2F	vec;

	vec.x = 0;
	vec.y = -0.66;
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
	_var()->o_player[i].plane = vec;
	_var()->o_player[i].hb.hit.r = 0.5;
	_var()->o_player[i].hb.n = 0;
	_var()->o_player[i].shoot_n = 0;
	dist = hypot(_var()->o_player[i].dx, _var()->o_player[i].dy);
	_var()->o_player[i].angle = 360
	- acos(_var()->o_player[i].dx / dist) * 180 / M_PI;
	init_data_shot(&_var()->o_player[i]);
}

void	ft_init_player2(void)
{
	double	dist;
	int		i;

	i = 0;
	dist = 0;
	while (i < MAX_PLAYER)
	{
		ft_init_player_2_values(i, dist);
		++i;
	}
}

static void	ft_generate_dsprite_next_one(void)
{
	_image()->dsprite[10] = generate_image(
		"./img/soldier/new_blue/back_west_2.xpm");
	_image()->dsprite[11] = generate_image(
		"./img/soldier/new_blue/back_west_1.xpm");
	_image()->dsprite[12] = generate_image(
		"./img/soldier/new_blue/west.xpm");
	_image()->dsprite[13] = generate_image(
		"./img/soldier/new_blue/front_west_3.xpm");
}

static void	ft_generate_dsprite_next_two(void)
{
	_image()->walk_sprite[0] = generate_image(
		"./img/soldier/new_blue/walk/front.xpm");
	_image()->walk_sprite[1] = generate_image(
		"./img/soldier/new_blue/walk/southeast.xpm");
	_image()->walk_sprite[2] = generate_image(
		"./img/soldier/new_blue/walk/east.xpm");
	_image()->walk_sprite[3] = generate_image(
		"./img/soldier/new_blue/walk/northeast.xpm");
	_image()->walk_sprite[4] = generate_image(
		"./img/soldier/new_blue/walk/back.xpm");
	_image()->walk_sprite[5] = generate_image(
		"./img/soldier/new_blue/walk/northwest.xpm");
	_image()->walk_sprite[6] = generate_image(
		"./img/soldier/new_blue/walk/west.xpm");
	_image()->walk_sprite[7] = generate_image(
		"./img/soldier/new_blue/walk/southwest.xpm");
	_image()->death_sprite = generate_image(
		"./img/soldier/new_blue/death.xpm");
	_image()->rifle = generate_image(
		"./img/soldier/rifle.xpm");
	_image()->dsprite[14] = generate_image(
		"./img/soldier/new_blue/front_west_2.xpm");
	_image()->dsprite[15] = generate_image(
		"./img/soldier/new_blue/front_west_1.xpm");
}

void	generate_dsprite(void)
{
	_image()->dsprite[0] = generate_image(
		"./img/soldier/new_blue/front.xpm");
	_image()->dsprite[1] = generate_image(
		"./img/soldier/new_blue/front_east_1.xpm");
	_image()->dsprite[2] = generate_image(
		"./img/soldier/new_blue/front_east_2.xpm");
	_image()->dsprite[3] = generate_image(
		"./img/soldier/new_blue/front_east_3.xpm");
	_image()->dsprite[4] = generate_image(
		"./img/soldier/new_blue/east.xpm");
	_image()->dsprite[5] = generate_image(
		"./img/soldier/new_blue/back_east_1.xpm");
	_image()->dsprite[6] = generate_image(
		"./img/soldier/new_blue/back_east_2.xpm");
	_image()->dsprite[7] = generate_image(
		"./img/soldier/new_blue/back_east_3.xpm");
	_image()->dsprite[8] = generate_image(
		"./img/soldier/new_blue/back.xpm");
	_image()->dsprite[9] = generate_image(
		"./img/soldier/new_blue/back_west_3.xpm");
	ft_generate_dsprite_next_one();
	ft_generate_dsprite_next_two();
}
