/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:05:00 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/16 01:41:40 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

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
		{
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
				ft_black_hole(0); // TODO FREE TOUT ICI
			_menu()->s_state[i].state = 
			ft_hitbox(_menu()->s_state[i].hitbox, _var()->m_pos);
		}
		i++;
	}
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
		{
			if (i == 0 && _menu()->p_state[0].state == 2)
			{
				_var()->nb_player = 2;
				_menu()->mode = MENU_PSEUDO;
				_var()->is_host = SERVER;
			}
			if (i == 1 && _menu()->p_state[1].state == 2)
			{
				_var()->nb_player = 4;
				_menu()->mode = MENU_PSEUDO;
				_var()->is_host = SERVER;
			}
			if (i == 2 && _menu()->p_state[2].state == 2)
			{
				_var()->nb_player = 6;
				_menu()->mode = MENU_PSEUDO;
				_var()->is_host = SERVER;
			}
			if (i == 3 && _menu()->p_state[3].state == 2)
			{
				_menu()->mode = MENU_IP;
				_var()->is_host = CLIENT;
			}
			_menu()->p_state[i].state = 
			ft_hitbox(_menu()->p_state[i].hitbox, _var()->m_pos);
		}
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

	i = 0;
	while (i < 7)
	{
		if (_menu()->o_state[i].state != 2 || (_menu()->o_state[i]
				.state == 2 && get_clock(_menu()->o_state[i].clock)
				> BUT_CL_TIME))
		{
			check_action_state_options(i);
			_menu()->o_state[i].state = 
			ft_hitbox(_menu()->o_state[i].hitbox, _var()->m_pos);
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

/*
-Loop for menu displaying.
*/
int	menu_loop(void)
{
	click_update();
	ft_play_music(MENU_MUSIC);
	if (_menu()->mode == INTRO)
		ft_intro();
	if (_menu()->mode == MENU_LEADERBOARD)
		ft_pong_client();
	else if(_menu()->mode == MENU_LOBBY
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

static int	is_nb_keycode(int k)
{
	if (k == ZERO || k == ONE || k == TWO || k == THREE || k == FOUR
		|| k == FIVE || k == SIX || k == SEVEN || k == EIGHT || k == NINE)
		return (1);
	return (0);
}

static int	get_nb_keycode(int k)
{
	if (k == ZERO)
		return ('0');
	if (k == ONE)
		return ('1');
	if (k == TWO)
		return ('2');
	if (k == THREE)
		return ('3');
	if (k == FOUR)
		return ('4');
	if (k == FIVE)
		return ('5');
	if (k == SIX)
		return ('6');
	if (k == SEVEN)
		return ('7');
	if (k == EIGHT)
		return ('8');
	if (k == NINE)
		return ('9');
	return ('0');
}

int	menu_hook_pseudo(int keycode)
{
	static int	n = 0;

	if (((keycode >= A_ && keycode <= Z) || is_nb_keycode(keycode)) && n + 1 < 17)
	{
		if (is_nb_keycode(keycode))
			_player()->pseudo[n++] = get_nb_keycode(keycode);
		else
			_player()->pseudo[n++] = keycode - 32;
		_player()->pseudo[n] = 0;
	}
	if (keycode == ERASE && n > 0)
	{
		n--;
		_player()->pseudo[n] = 0;
	}
	if (keycode == ENTER && n > 3 && _var()->is_host == SERVER)
	{
		_menu()->mode = MENU_LOBBY;
		_var()->mode = ONLINE_START;
	}
	if (keycode == ENTER && n > 3 && _var()->is_host == CLIENT)
	{
		if (ft_init_client() == EXIT_FAILURE)
		{
			_player()->pseudo[0] = 0;
			n = 0;
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

int	menu_hook_ip(int keycode)
{
	if (keycode == ZERO && _menu()->n_ip + 1 < 16)
	{
		_var()->ip[_menu()->n_ip++] = '0';
		_var()->ip[_menu()->n_ip] = 0;
	}
	if (keycode == ONE && _menu()->n_ip + 1 < 16)
	{
		_var()->ip[_menu()->n_ip++] = '1';
		_var()->ip[_menu()->n_ip] = 0;
	}
	if (keycode == TWO && _menu()->n_ip + 1 < 16)
	{
		_var()->ip[_menu()->n_ip++] = '2';
		_var()->ip[_menu()->n_ip] = 0;
	}
	if (keycode == THREE && _menu()->n_ip + 1 < 16)
	{
		_var()->ip[_menu()->n_ip++] = '3';
		_var()->ip[_menu()->n_ip] = 0;
	}
	if (keycode == FOUR && _menu()->n_ip + 1 < 16)
	{
		_var()->ip[_menu()->n_ip++] = '4';
		_var()->ip[_menu()->n_ip] = 0;
	}
	if (keycode == FIVE && _menu()->n_ip + 1 < 16)
	{
		_var()->ip[_menu()->n_ip++] = '5';
		_var()->ip[_menu()->n_ip] = 0;
	}
	if (keycode == SIX && _menu()->n_ip + 1 < 16)
	{
		_var()->ip[_menu()->n_ip++] = '6';
		_var()->ip[_menu()->n_ip] = 0;
	}
	if (keycode == SEVEN && _menu()->n_ip + 1 < 16)
	{
		_var()->ip[_menu()->n_ip++] = '7';
		_var()->ip[_menu()->n_ip] = 0;
	}
	if (keycode == EIGHT && _menu()->n_ip + 1 < 16)
	{
		_var()->ip[_menu()->n_ip++] = '8';
		_var()->ip[_menu()->n_ip] = 0;
	}
	if (keycode == NINE && _menu()->n_ip + 1 < 16)
	{
		_var()->ip[_menu()->n_ip++] = '9';
		_var()->ip[_menu()->n_ip] = 0;
	}
	if (keycode == SPACE && _menu()->n_ip + 1 < 16)
	{
		_var()->ip[_menu()->n_ip++] = '.';
		_var()->ip[_menu()->n_ip] = 0;
	}
	if (keycode == ERASE && _menu()->n_ip > 0)
	{
		_menu()->n_ip--;
		_var()->ip[_menu()->n_ip] = 0;
	}
	if (keycode == ENTER && _menu()->n_ip > 2 && _var()->is_host == CLIENT)
	{
		_menu()->mode = MENU_PSEUDO;
		_var()->mode = MENU;
	}
	return (0);
}
