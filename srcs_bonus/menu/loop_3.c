/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:56:21 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

/*
-Function that check if button is hover and change it state for menu_options.
*/
void	check_action_state_options(int i)
{
	if (i == 0 && _menu()->o_state[0].state == 2)
	{
		if (_menu()->mute_s_state == MUTE_S)
			_menu()->mute_s_state = SOUND;
		else
			_menu()->mute_s_state = MUTE_S;
	}
	if (i == 3 && _menu()->o_state[3].state == 2)
	{
		if (_menu()->mute_m_state == MUTE_M)
			_menu()->mute_m_state = MUSIC;
		else
			_menu()->mute_m_state = MUTE_M;
	}
	if (i == 6 && _menu()->o_state[6].state == 2)
	{
		_menu()->mode = MENU_START;
		restart_button();
	}
	check_action_state_bar(i);
}

/*
-Function that call the good action in terms of the buttons clicked.
*/
void	check_button_state_options(void)
{
	int	i;
	int	hit;

	i = 0;
	while (i < 7)
	{
		if (_menu()->o_state[i].state != 2 || (_menu()->o_state[i]
				.state == 2 && get_clock(_menu()->o_state[i].clock)
				> BUT_CL_TIME))
		{
			hit = ft_hitbox(_menu()->o_state[i].hitbox, _var()->m_pos);
			check_action_state_options(i);
			_menu()->o_state[i].state = hit;
		}
		i++;
	}
}

/*
-Planet frame calculation
*/
void	planet_clock(void)
{
	if (get_clock(_var()->clock) - _menu()->start > 100000)
	{
		_menu()->n++;
		if (_menu()->n >= 120)
			_menu()->n = 0;
		if (!((_menu()->n + 1) % 12))
		{
			_menu()->n = 0;
			_menu()->ny++;
		}
		if (_menu()->ny >= 10)
			_menu()->ny = 0;
		_menu()->start = get_clock(_var()->clock);
	}
}

void	menu_call_hook(void)
{
	if (_menu()->mode == MENU_START)
		menu_start();
	else if (_menu()->mode == MENU_PLAYER)
		menu_player();
	else if (_menu()->mode == MENU_PSEUDO)
		menu_pseudo();
	else if (_menu()->mode == MENU_IP)
		menu_ip();
	else if (_menu()->mode == MENU_LOBBY)
		menu_lobby();
	else if (_menu()->mode == MENU_OPTION)
		menu_option();
	else if (_menu()->mode == MENU_LEADERBOARD)
		menu_leaderboard();
	mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win,
		_img()->img, 0, 0);
}
