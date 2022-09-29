/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:05:00 by denissereno       #+#    #+#             */
/*   Updated: 2022/09/29 13:21:08 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"
#include <unistd.h>

/*
-Function that check if button is hover and change it state for menu_start.
*/
void	check_button_state(void)
{
	if (_var()->menu->s_state[0].state != 2)
		_var()->menu->s_state[0].state = 
		ft_hitbox(_var()->menu->s_state[0].hitbox, _var()->m_pos);
	if (_var()->menu->s_state[1].state != 2)
		_var()->menu->s_state[1].state = 
		ft_hitbox(_var()->menu->s_state[1].hitbox, _var()->m_pos);
	if (_var()->menu->s_state[2].state != 2)
		_var()->menu->s_state[2].state = 
		ft_hitbox(_var()->menu->s_state[2].hitbox, _var()->m_pos);
	if (_var()->menu->s_state[3].state != 2)
		_var()->menu->s_state[3].state = 
		ft_hitbox(_var()->menu->s_state[3].hitbox, _var()->m_pos);
}

/*
-Function that check if button is hover and change it state for menu_options.
*/
void	check_button_state_options(void)
{
	if (_var()->menu->o_state[0].state != 2)
		_var()->menu->o_state[0].state = 
		ft_hitbox(_var()->menu->o_state[0].hitbox, _var()->m_pos);
	if (_var()->menu->o_state[1].state != 2)
		_var()->menu->o_state[1].state = 
		ft_hitbox(_var()->menu->o_state[1].hitbox, _var()->m_pos);
	if (_var()->menu->o_state[2].state != 2)
		_var()->menu->o_state[2].state = 
		ft_hitbox(_var()->menu->o_state[2].hitbox, _var()->m_pos);
	if (_var()->menu->o_state[3].state != 2)
		_var()->menu->o_state[3].state = 
		ft_hitbox(_var()->menu->o_state[3].hitbox, _var()->m_pos);
	if (_var()->menu->o_state[4].state != 2)
		_var()->menu->o_state[4].state = 
		ft_hitbox(_var()->menu->o_state[4].hitbox, _var()->m_pos);
	if (_var()->menu->o_state[5].state != 2)
		_var()->menu->o_state[5].state = 
		ft_hitbox(_var()->menu->o_state[5].hitbox, _var()->m_pos);
	if (_var()->menu->o_state[6].state != 2)
		_var()->menu->o_state[6].state = 
		ft_hitbox(_var()->menu->o_state[6].hitbox, _var()->m_pos);
}

/*
-Loop for menu displaying.
*/
int	menu_loop(void)
{
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
