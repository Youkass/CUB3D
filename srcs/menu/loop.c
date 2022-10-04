/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:05:00 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/02 14:27:59 by denissereno      ###   ########.fr       */
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
		if (_var()->menu->s_state[i].state != 2 || (_var()->menu->s_state[i]
				.state == 2 && get_clock(_var()->menu->s_state[i].clock)
				> BUT_CL_TIME))
		{
			if (i == 0 && _var()->menu->s_state[0].state == 2)
				_var()->mode = GAME;
			if (i == 1 && _var()->menu->s_state[1].state == 2)
				_var()->menu->mode = MENU_OPTION;
			if (i == 3 && _var()->menu->s_state[3].state == 2)
				exit(0); // TODO FREE TOUT ICI
			_var()->menu->s_state[i].state = 
			ft_hitbox(_var()->menu->s_state[i].hitbox, _var()->m_pos);
		}
		i++;
	}
}

/*
-Function that increment the bar when arrow is clicked
*/
void	check_action_state_bar(int i)
{
	if (i == 1 && _var()->menu->o_state[1].state == 2
		&& _var()->menu->s_bar > 0)
	{
		_var()->menu->s_bar -= 5;
		_var()->menu->pos_s_bar.x -= 5 * BAR_INC;
	}
	if (i == 2 && _var()->menu->o_state[2].state == 2
		&& _var()->menu->s_bar < 100)
	{
		_var()->menu->s_bar += 5;
		_var()->menu->pos_s_bar.x += 5 * BAR_INC;
	}
	if (i == 4 && _var()->menu->o_state[4].state == 2
		&& _var()->menu->s_bar > 0)
	{
		_var()->menu->m_bar -= 5;
		_var()->menu->pos_m_bar.x -= 5 * BAR_INC;
	}
	if (i == 5 && _var()->menu->o_state[5].state == 2
		&& _var()->menu->m_bar < 100)
	{
		_var()->menu->m_bar += 5;
		_var()->menu->pos_s_bar.x += 5 * BAR_INC;
	}
}

/*
-Function that check if button is hover and change it state for menu_options.
*/
void	check_action_state_options(int i)
{
	if (i == 0 && _var()->menu->o_state[0].state == 2)
	{
		if (_var()->menu->mute_s_state == MUTE_S)
			_var()->menu->mute_s_state = SOUND;
		else
			_var()->menu->mute_s_state = MUTE_S;
	}
	if (i == 3 && _var()->menu->o_state[3].state == 2)
	{
		if (_var()->menu->mute_m_state == MUTE_M)
			_var()->menu->mute_m_state = MUSIC;
		else
			_var()->menu->mute_m_state = MUTE_M;
	}
	if (i == 6 && _var()->menu->o_state[6].state == 2)
	{
		_var()->menu->mode = MENU_START;
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
		if (_var()->menu->o_state[i].state != 2 || (_var()->menu->o_state[i]
				.state == 2 && get_clock(_var()->menu->o_state[i].clock)
				> BUT_CL_TIME))
		{
			check_action_state_options(i);
			_var()->menu->o_state[i].state = 
			ft_hitbox(_var()->menu->o_state[i].hitbox, _var()->m_pos);
		}
		i++;
	}
}

/*
-Loop for menu displaying.
*/
int	menu_loop(void)
{
	drag_bar();
	if (_var()->menu->mode == MENU_START)
		check_button_state();
	else if (_var()->menu->mode == MENU_OPTION)
		check_button_state_options();
	mlx_mouse_get_pos(_mlx()->mlx, _mlx()->mlx_win,
		&_var()->m_pos.x, &_var()->m_pos.y);
	if (_var()->menu->mode == MENU_START)
		menu_start();
	else if (_var()->menu->mode == MENU_OPTION)
		menu_option();
	
	mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win,
		_var()->menu->img.img, 0, 0);
	return (0);
}
/*
-Function for loop inputs.
*/
int	menu_hook(int keycode)
{
	int			i;
	t_enum_key	tab[1];

	i = 0;
	tab[0].id= 65307;
	tab[0].ft_hook_key = &ft_escape;
	while (i < MAX_KEYS)
	{
		if (tab[i].id == keycode)
			return (tab[i].ft_hook_key());
		++i;
	}
	return (0);
}
