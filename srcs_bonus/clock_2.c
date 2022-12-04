/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 19:05:31 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub.h"

void	walk_clock(void)
{
	if (get_clock(_var()->clock) - _var()->walk_start > 50000)
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
	if (get_clock(_var()->clock) - _player()->death_start > 50000)
	{
		_player()->death_n++;
		if (_player()->death_n >= 16)
			_player()->death_n = 15;
		_player()->death_start = get_clock(_var()->clock);
	}
}

void	reload_clock(void)
{
	if (get_clock(_var()->clock) - _player()->start_reload
		> _weapon()[_player()->weapon_id]->reload_ms)
	{
		_player()->can_shoot = 1;
		_player()->is_shooting = 0;
	}
}
