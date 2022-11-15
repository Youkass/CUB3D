/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 21:50:20 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/15 22:42:18 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_weapons(void)
{
	_weapon()[0]->name = ft_malloc(sizeof(char) * 6);
	_weapon()[0]->name = "Rifle\0";
	_weapon()[0]->id = 0;
	_weapon()[0]->range = 25;
	_weapon()[0]->power = 15;
	_weapon()[0]->reload_ms = 150000;
	_weapon()[0]->ammo = 15;
	_weapon()[0]->full_ammo = 45;
	_weapon()[0]->headshot = 25;
	_weapon()[0]->footshot = 5;
	_weapon()[0]->anim_shotms = 100000;
	_weapon()[0]->shot_frames = 3;
	_weapon()[0]->reload_frames = 8;

	_weapon()[1]->name = ft_malloc(sizeof(char) * 4);
	_weapon()[1]->name = "Gun\0";
	_weapon()[1]->id = 0;
	_weapon()[1]->range = 2;
	_weapon()[1]->power = 30;
	_weapon()[1]->reload_ms = 1500000;
	_weapon()[1]->ammo = 8;
	_weapon()[1]->full_ammo = 32;
	_weapon()[1]->headshot = 40;
	_weapon()[1]->footshot = 20;
	_weapon()[1]->anim_shotms = 100000;
	_weapon()[1]->shot_frames = 6;
	_weapon()[1]->reload_frames = 4;

	_weapon()[2]->name = ft_malloc(sizeof(char) * 6);
	_weapon()[2]->name = "Knife\0";
	_weapon()[2]->id = 0;
	_weapon()[2]->range = 2;
	_weapon()[2]->power = 50;
	_weapon()[2]->reload_ms = 2500000;
	_weapon()[2]->ammo = 9999;
	_weapon()[2]->full_ammo = 45;
	_weapon()[2]->headshot = 200;
	_weapon()[2]->footshot = 100;
	_weapon()[2]->anim_shotms = 10000;
	_weapon()[2]->shot_frames = 1;
	_weapon()[2]->reload_frames = 0;
}