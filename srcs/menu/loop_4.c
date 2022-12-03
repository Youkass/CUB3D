/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:56:21 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 18:57:43 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	compute_hitbox_buttons(int i)
{
	int	hit;

	hit = ft_hitbox(_menu()->s_state[i].hitbox, _var()->m_pos);
	if (i == 0 && _menu()->s_state[0].state == 2)
	{
		_var()->nb_player = 1;
		_var()->mode = GAME;
	}
	if (i == 1 && _menu()->s_state[1].state == 2)
		_menu()->mode = MENU_PLAYER;
	if (i == 2 && _menu()->s_state[2].state == 2)
		_menu()->mode = MENU_OPTION;
	if (i == 3 && _menu()->s_state[3].state == 2)
		ft_black_hole(0);
	_menu()->s_state[i].state = hit;
}

/*
-Function that check if button is hover and change it state for menu_start.
*/
void	check_button_state(void)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (_menu()->s_state[i].state != 2 || (_menu()->s_state[i]
				.state == 2 && get_clock(_menu()->s_state[i].clock)
				> BUT_CL_TIME))
			compute_hitbox_buttons(i);
		i++;
	}
}

void	compute_hitbox_pl(int i)
{
	int	hit;

	hit = ft_hitbox(_menu()->p_state[i].hitbox, _var()->m_pos);
	if (i == 0 && _menu()->p_state[0].state == 2)
	{
		_var()->nb_player = 10;
		_menu()->mode = MENU_PSEUDO;
		_var()->is_host = SERVER;
	}
	if (i == 3 && _menu()->p_state[3].state == 2)
	{
		_menu()->mode = MENU_IP;
		_var()->is_host = CLIENT;
	}
	_menu()->p_state[i].state = hit;
}

void	check_button_state_pl(void)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (_menu()->p_state[i].state != 2 || (_menu()->p_state[i]
				.state == 2 && get_clock(_menu()->p_state[i].clock)
				> BUT_CL_TIME))
			compute_hitbox_pl(i);
		i++;
	}
}

/*
-Function that increment the bar when arrow is clicked
*/
void	check_action_state_bar(int i)
{
	if (i == 1 && _menu()->o_state[1].state == 2
		&& _menu()->s_bar > 0)
	{
		_menu()->s_bar -= 5;
		_menu()->pos_s_bar.x -= 5 * BAR_INC;
	}
	if (i == 2 && _menu()->o_state[2].state == 2
		&& _menu()->s_bar < 100)
	{
		_menu()->s_bar += 5;
		_menu()->pos_s_bar.x += 5 * BAR_INC;
	}
	if (i == 4 && _menu()->o_state[4].state == 2
		&& _menu()->s_bar > 0)
	{
		_menu()->m_bar -= 5;
		_menu()->pos_m_bar.x -= 5 * BAR_INC;
	}
	if (i == 5 && _menu()->o_state[5].state == 2
		&& _menu()->m_bar < 100)
	{
		_menu()->m_bar += 5;
		_menu()->pos_s_bar.x += 5 * BAR_INC;
	}
}
