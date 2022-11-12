/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 21:50:20 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/11 21:50:26 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_weapons(void)
{
	_weapon()[0]->name = malloc(sizeof(char) * 6);
	_weapon()[0]->name = "Rifle\0";
	_weapon()[0]->id = 0;
	_weapon()[0]->range = 25;
	_weapon()[0]->power = 25;
	_weapon()[0]->reload_ms = 500000;
	_weapon()[0]->ammo = 15;
	_weapon()[0]->full_ammo = 45;
	_weapon()[0]->headshot = 50;
	_weapon()[0]->footshot = 10;
	_weapon()[1]->name = malloc(sizeof(char) * 6);
	_weapon()[1]->name = "Couteau\0";
	_weapon()[1]->id = 0;
	_weapon()[1]->range = 2;
	_weapon()[1]->power = 100;
	_weapon()[1]->reload_ms = 500000;
	_weapon()[1]->ammo = 9999;
	_weapon()[1]->full_ammo = 45;
	_weapon()[1]->headshot = 200;
	_weapon()[1]->footshot = 100;
}