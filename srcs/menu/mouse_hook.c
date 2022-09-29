/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:04:44 by denissereno       #+#    #+#             */
/*   Updated: 2022/09/29 13:10:09 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	check_button_state_mouse(int kc)
{
	if (kc == 1 && ft_hitbox(_var()->menu->s_state[0].hitbox, _var()->m_pos))
	{
		_var()->menu->s_state[0].state = 2;
		_var()->mode = GAME;
	}
	if (kc == 1 && ft_hitbox(_var()->menu->s_state[1].hitbox, _var()->m_pos))
	{
		_var()->menu->s_state[1].state = 2;
		_var()->menu->mode = MENU_OPTION;
	}
	if (kc == 1 && ft_hitbox(_var()->menu->s_state[2].hitbox, _var()->m_pos))
		_var()->menu->s_state[2].state = 2;
	if (kc == 1 && ft_hitbox(_var()->menu->s_state[3].hitbox, _var()->m_pos))
	{
		_var()->menu->s_state[3].state = 2;
		// TODO FREE TOUT
		exit(0);
	}
}

void	check_button_state_mouse_options(int kc)
{
	if (kc == 1 && ft_hitbox(_var()->menu->o_state[0].hitbox, _var()->m_pos))
		_var()->menu->o_state[0].state = 2;
	if (kc == 1 && ft_hitbox(_var()->menu->o_state[1].hitbox, _var()->m_pos))
		_var()->menu->o_state[1].state = 2;
	if (kc == 1 && ft_hitbox(_var()->menu->o_state[2].hitbox, _var()->m_pos))
		_var()->menu->o_state[2].state = 2;
	if (kc == 1 && ft_hitbox(_var()->menu->o_state[3].hitbox, _var()->m_pos))
		_var()->menu->o_state[3].state = 2;
	if (kc == 1 && ft_hitbox(_var()->menu->o_state[4].hitbox, _var()->m_pos))
		_var()->menu->o_state[4].state = 2;
	if (kc == 1 && ft_hitbox(_var()->menu->o_state[5].hitbox, _var()->m_pos))
		_var()->menu->o_state[5].state = 2;
	if (kc == 1 && ft_hitbox(_var()->menu->o_state[6].hitbox, _var()->m_pos))
	{
		_var()->menu->o_state[6].state = 2;
		_var()->menu->mode = MENU_START;
		restart_button();
	}
}

/*
-Function for menu mouse inputs.
*/
int	menu_mouse_hook(int keycode)
{
	if (_var()->menu->mode == MENU_START)
		check_button_state_mouse(keycode);
	if (_var()->menu->mode == MENU_OPTION)
		check_button_state_mouse_options(keycode);
	return (0);
}
