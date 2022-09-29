/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:04:44 by denissereno       #+#    #+#             */
/*   Updated: 2022/09/29 16:51:27 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	check_button_state_mouse(int kc)
{
	int	i;

	i = 0;
	(void)kc;
	while (i < 4)
	{
		if (_var()->key.mouse && ft_hitbox(_var()->menu->s_state[i].hitbox,
				_var()->m_pos))
		{
			_var()->menu->s_state[i].state = 2;
			_var()->menu->s_state[i].clock = start_clock();
			break ;
		}
		i++;
	}
}

/*

Coder une drag bar : Stocker a quelle position est la fin de la barre.
Creer une hitbox de environ 20px * 20px autour de la dernier ligne de la barre.
Si c'est dans la hitbox est que le mouse_click est a 1 on drag, quand il passe 
a zero on stop.
Si la position de la souris est inferieur a la barre - 5% alors on diminue de 5%
sinon si c'est supérieur a la barre + 5% alors on incremente de 5% sinon on ne 
fait rien.
*/

void	check_button_state_mouse_options(int kc)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (kc == 1 && ft_hitbox(_var()->menu->o_state[i].hitbox,
				_var()->m_pos) && _var()->menu->o_state[i].state != 2)
		{
			_var()->menu->o_state[i].state = 2;
			_var()->menu->o_state[i].clock = start_clock();
			break ;
		}
		i++;
	}
}

/*
-Function for menu mouse inputs.
*/
int	menu_mouse_hook(int keycode)
{
	if (keycode == 1)
		_var()->key.mouse = 1;
	if (_var()->menu->mode == MENU_START)
		check_button_state_mouse(keycode);
	if (_var()->menu->mode == MENU_OPTION)
		check_button_state_mouse_options(keycode);
	return (0);
}
