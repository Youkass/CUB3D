/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 21:50:20 by denissereno       #+#    #+#             */
/*   Updated: 2022/12/03 19:26:18 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	ft_generate_dsprite_red_next(void)
{
	_image()->dsprite_red[12] = generate_image(
		"./img/soldier/red/west.xpm");
	_image()->dsprite_red[13] = generate_image(
		"./img/soldier/red/front_west_3.xpm");
	_image()->dsprite_red[14] = generate_image(
		"./img/soldier/red/front_west_2.xpm");
	_image()->dsprite_red[15] = generate_image(
		"./img/soldier/red/front_west_1.xpm");
	_image()->walk_sprite_red[0] = generate_image(
		"./img/soldier/red/walk/front.xpm");
	_image()->walk_sprite_red[1] = generate_image(
		"./img/soldier/red/walk/southeast.xpm");
	_image()->walk_sprite_red[2] = generate_image(
		"./img/soldier/red/walk/east.xpm");
	_image()->walk_sprite_red[3] = generate_image(
		"./img/soldier/red/walk/northeast.xpm");
	_image()->walk_sprite_red[4] = generate_image(
		"./img/soldier/red/walk/back.xpm");
	_image()->walk_sprite_red[5] = generate_image(
		"./img/soldier/red/walk/northwest.xpm");
	_image()->walk_sprite_red[6] = generate_image(
		"./img/soldier/red/walk/west.xpm");
}

static void	ft_generate_dsprite_red_next_two(void)
{
	_image()->walk_sprite_red[7] = generate_image(
		"./img/soldier/red/walk/southwest.xpm");
	_image()->death_sprite_red = generate_image(
		"./img/soldier/red/death.xpm");
}

void	generate_dsprite_red(void)
{
	_image()->dsprite_red[0] = generate_image("./img/soldier/red/front.xpm");
	_image()->dsprite_red[1] = generate_image(
		"./img/soldier/red/front_east_1.xpm");
	_image()->dsprite_red[2] = generate_image(
		"./img/soldier/red/front_east_2.xpm");
	_image()->dsprite_red[3] = generate_image(
		"./img/soldier/red/front_east_3.xpm");
	_image()->dsprite_red[4] = generate_image(
		"./img/soldier/red/east.xpm");
	_image()->dsprite_red[5] = generate_image(
		"./img/soldier/red/back_east_1.xpm");
	_image()->dsprite_red[6] = generate_image(
		"./img/soldier/red/back_east_2.xpm");
	_image()->dsprite_red[7] = generate_image(
		"./img/soldier/red/back_east_3.xpm");
	_image()->dsprite_red[8] = generate_image(
		"./img/soldier/red/back.xpm");
	_image()->dsprite_red[9] = generate_image(
		"./img/soldier/red/back_west_3.xpm");
	_image()->dsprite_red[10] = generate_image(
		"./img/soldier/red/back_west_2.xpm");
	_image()->dsprite_red[11] = generate_image(
		"./img/soldier/red/back_west_1.xpm");
	ft_generate_dsprite_red_next();
	ft_generate_dsprite_red_next_two();
}

static void	ft_init_player_pos_next(void)
{
	double		dist;
	t_vector2F	vec;

	vec.x = 0;
	vec.y = -0.66;
	_player()->change_team = -1;
	_player()->scale = 0.8;
	_player()->dx = -0.50;
	_player()->shooted.id = -1;
	_player()->plane = vec;
	_player()->hb.hit.r = 0.5;
	generate_dsprite();
	generate_dsprite_red();
	_image()->sprite = generate_image("./img/front.xpm");
	dist = hypot(_player()->dx, _player()->dy);
	_player()->angle = 360 - acos(_player()->dx / dist) * 180 / M_PI;
	init_data_shot(_player());
}

void	ft_init_player_pos(void)
{
	int	i;

	_player()->team = TEAM_VOID;
	memset(_var()->blue, 0, sizeof(_var()->blue));
	memset(_var()->red, 0, sizeof(_var()->red));
	memset(_var()->neutral, 0, sizeof(_var()->neutral));
	memset(&_player()->kill_match, 0, sizeof(_player()->kill_match));
	memset(&_player()->kill_round, 0, sizeof(_player()->kill_round));
	_log()->log = NULL;
	_player()->spec_id = -1;
	_player()->exchange = 4;
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
	ft_init_player_pos_next();
}
