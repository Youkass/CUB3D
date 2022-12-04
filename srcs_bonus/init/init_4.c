/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:01:34 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

void	ft_init_one(void)
{
	_weapon()[0]->name = ft_malloc(sizeof(char) * 6);
	_weapon()[0]->name = "Rifle\0";
	_weapon()[0]->id = 0;
	_weapon()[0]->range = 99;
	_weapon()[0]->power = 15;
	_weapon()[0]->reload_ms = 200000;
	_weapon()[0]->ammo = 15;
	_weapon()[0]->full_ammo = 45;
	_weapon()[0]->headshot = 25;
	_weapon()[0]->footshot = 5;
	_weapon()[0]->anim_reloadms = 800000;
	_weapon()[0]->shot_frames = 3;
	_weapon()[0]->reload_frames = 8;
	_weapon()[1]->name = ft_malloc(sizeof(char) * 4);
	_weapon()[1]->name = "Gun\0";
	_weapon()[1]->id = 0;
	_weapon()[1]->range = 99;
	_weapon()[1]->power = 30;
	_weapon()[1]->reload_ms = 300000;
	_weapon()[1]->ammo = 8;
	_weapon()[1]->full_ammo = 32;
	_weapon()[1]->headshot = 40;
	_weapon()[1]->footshot = 20;
	_weapon()[1]->anim_reloadms = 600000;
	_weapon()[1]->shot_frames = 6;
}

void	init_weapons(void)
{
	ft_init_one();
	_weapon()[1]->reload_frames = 4;
	_weapon()[2]->name = ft_malloc(sizeof(char) * 6);
	_weapon()[2]->name = "Knife\0";
	_weapon()[2]->id = 0;
	_weapon()[2]->range = 2;
	_weapon()[2]->power = 50;
	_weapon()[2]->reload_ms = 250000;
	_weapon()[2]->ammo = 9999;
	_weapon()[2]->full_ammo = 45;
	_weapon()[2]->headshot = 200;
	_weapon()[2]->footshot = 100;
	_weapon()[2]->anim_reloadms = 250000;
	_weapon()[2]->shot_frames = 1;
	_weapon()[2]->reload_frames = 0;
}

void	ft_init_key_next(void)
{
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
	ft_init_key_next();
}

void	ft_init_var_next(void)
{
	int	i;

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
