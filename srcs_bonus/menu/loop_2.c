/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:56:21 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/05 19:53:47 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

/*
-Loop for menu displaying.
*/
int	menu_loop(void)
{
	mlx_mouse_show(_mlx()->mlx, _mlx()->mlx_win);
	ft_play_music(MENU_MUSIC);
	if (_menu()->mode == INTRO)
		ft_intro();
	if (_menu()->mode == MENU_LEADERBOARD)
		ft_pong_client();
	else if (_menu()->mode == MENU_LOBBY
		&& (_var()->mode != GAME
			&& _var()->mode != GAME_START_ONLINE))
		menu_pong();
	drag_bar();
	if (_menu()->mode == MENU_START)
		check_button_state();
	else if (_menu()->mode == MENU_PLAYER)
		check_button_state_pl();
	else if (_menu()->mode == MENU_OPTION)
		check_button_state_options();
	mlx_mouse_get_pos(_mlx()->mlx, _mlx()->mlx_win,
		&_var()->m_pos.x, &_var()->m_pos.y);
	menu_call_hook();
	return (0);
}

/*
-Function for loop inputs.
*/
int	menu_hook(int keycode)
{
	if (keycode == ESC)
		ft_escape();
	return (0);
}

int	is_nb_keycode(int k)
{
	if ((k == ZERO || k == ONE || k == TWO || k == THREE || k == FOUR
			|| k == FIVE || k == SIX || k == SEVEN || k == EIGHT || k == NINE)
		|| (k == ZERO_PAV || k == ONE_PAV || k == TWO_PAV || k == THREE_PAV
			|| k == FOUR_PAV || k == FIVE_PAV || k == SIX_PAV || k == SEVEN_PAV
			|| k == EIGHT_PAV || k == NINE_PAV))
		return (1);
	return (0);
}

int	get_nb_keycode(int k)
{
	if (k == ZERO || k == ZERO_PAV)
		return ('0');
	if (k == ONE || k == ONE_PAV)
		return ('1');
	if (k == TWO || k == TWO_PAV)
		return ('2');
	if (k == THREE || k == THREE_PAV)
		return ('3');
	if (k == FOUR || k == FOUR_PAV)
		return ('4');
	if (k == FIVE || k == FIVE_PAV)
		return ('5');
	if (k == SIX || k == SIX_PAV)
		return ('6');
	if (k == SEVEN || k == SEVEN_PAV)
		return ('7');
	if (k == EIGHT || k == EIGHT_PAV)
		return ('8');
	if (k == NINE || k == NINE_PAV)
		return ('9');
	return ('0');
}

int	menu_hook_pseudo_2(int keycode, int *n)
{
	if (keycode == ENTER && *n > 3 && _var()->is_host == SERVER)
	{
		_menu()->mode = MENU_LOBBY;
		_var()->mode = ONLINE_START;
	}
	if (keycode == ENTER && *n > 3 && _var()->is_host == CLIENT)
	{
		if (ft_init_client() == EXIT_FAILURE)
		{
			_player()->pseudo[0] = 0;
			*n = 0;
			_var()->ip[0] = 0;
			_menu()->n_ip = 0;
			_menu()->mode = MENU_START;
			_var()->mode = MENU;
			return (0);
		}
		printf("je passe en mode lobby\n");
		_menu()->mode = MENU_LOBBY;
		_var()->mode = MENU;
	}
	return (0);
}
