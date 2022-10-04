/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dragbar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:07:18 by denissereno       #+#    #+#             */
/*   Updated: 2022/09/29 17:08:49 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	s_bar_drag(void)
{
	if (_var()->m_pos.x <= _var()->menu->pos_s_bar.x - (5 * BAR_INC)
		&& _var()->menu->s_bar > 0)
	{
		_var()->menu->pos_s_bar.x -= (5 * BAR_INC);
		_var()->menu->s_bar -= 5;
	}
	if (_var()->m_pos.x >= _var()->menu->pos_s_bar.x + (5 * BAR_INC)
		&& _var()->menu->s_bar < 100)
	{
		_var()->menu->pos_s_bar.x += (5 * BAR_INC);
		_var()->menu->s_bar += 5;
	}
}

void	m_bar_drag(void)
{
	if (_var()->m_pos.x <= _var()->menu->pos_m_bar.x - (5 * BAR_INC)
		&& _var()->menu->m_bar > 0)
	{
		_var()->menu->pos_m_bar.x -= (5 * BAR_INC);
		_var()->menu->m_bar -= 5;
	}
	if (_var()->m_pos.x >= _var()->menu->pos_m_bar.x + (5 * BAR_INC)
		&& _var()->menu->m_bar < 100)
	{
		_var()->menu->pos_m_bar.x += (5 * BAR_INC);
		_var()->menu->m_bar += 5;
	}
}


/*
-This function create a hitbox of 40 * 40px around the end of the sound and music
bar. If the mouse is in and is mouse clicking that call a function that will
check if the position of the mouse is over or under the next 5% of the volume
and if it is its increment or decrement the size of bar by 5%.
*/
void	drag_bar(void)
{
	if (ft_hitbox((t_vector2D[4]){{_var()->menu->pos_s_bar.x - 30,
				_var()->menu->pos_s_bar.y - 30}, {_var()->menu->pos_s_bar.x
				+ 30, _var()->menu->pos_s_bar.y - 30},  {_var()->menu
				->pos_s_bar.x - 30, _var()->menu->pos_s_bar.y + 30},
			{_var()->menu->pos_s_bar.x + 2, _var()->menu->pos_s_bar.y
				+ 30}}, _var()->m_pos) && _var()->key.mouse
			&& !_var()->menu->draging_s)
		_var()->menu->draging_s = 1;
	if (!_var()->key.mouse)
		_var()->menu->draging_s = 0;
	if (_var()->menu->draging_s)
		s_bar_drag();

	if (ft_hitbox((t_vector2D[4]){{_var()->menu->pos_m_bar.x - 30,
				_var()->menu->pos_m_bar.y - 30}, {_var()->menu->pos_m_bar.x
				+ 30, _var()->menu->pos_m_bar.y - 30},  {_var()->menu
				->pos_m_bar.x - 30, _var()->menu->pos_m_bar.y + 30},
			{_var()->menu->pos_m_bar.x + 2, _var()->menu->pos_m_bar.y
				+ 30}}, _var()->m_pos) && _var()->key.mouse
			&& !_var()->menu->draging_m)
		_var()->menu->draging_m = 1;
	if (!_var()->key.mouse)
		_var()->menu->draging_m = 0;
	if (_var()->menu->draging_m)
		m_bar_drag();

}
