/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:05:50 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/03 18:57:03 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/*
-Display starting menu
*/
void	menu_start(void)
{
	ft_put_image_to_image(_var()->menu->img, _var()->menu->bg,
		(t_vector2D){0, 0});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->logo,
		(t_vector2D){716 - OFFSET_X - 45, 155 - OFFSET_Y + 50});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons
	[_var()->menu->s_state[0].state][PLAY], (t_vector2D){861 - OFFSET_X,
		450 - OFFSET_Y});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons
	[_var()->menu->s_state[1].state][OPTIONS], (t_vector2D){861 - OFFSET_X,
		550 - OFFSET_Y});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons
	[_var()->menu->s_state[2].state][CREDITS], (t_vector2D){861 - OFFSET_X,
		650 - OFFSET_Y});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons
	[_var()->menu->s_state[3].state][EXIT], (t_vector2D){861 - OFFSET_X,
		750 - OFFSET_Y});
}

/*
-Display bottoms button of menu_options.
*/
static void	menu_bot_options(void)
{
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons[_var()
		->menu->o_state[3].state][_var()->menu->mute_m_state],
		_var()->menu->o_state[3].hitbox[0]);
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons[_var()->menu
		->o_state[4].state][L_ARR], _var()->menu->o_state[4].hitbox[0]);
	ft_put_image_to_image(_var()->menu->img, _var()->menu->bar[EMPTY][BAR_LEFT],
		(t_vector2D){819 - OFFSET_X, 542 - OFFSET_Y});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->bar[EMPTY][BAR_MID],
		(t_vector2D){912 - OFFSET_X, 542 - OFFSET_Y});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->bar[EMPTY]
	[BAR_RIGHT], (t_vector2D){1005 - OFFSET_X, 542 - OFFSET_Y});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons[_var()->menu
		->o_state[5].state][R_ARR], _var()->menu->o_state[5].hitbox[0]);
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons[_var()->menu
		->o_state[6].state][QUIT], _var()->menu->o_state[6].hitbox[0]);
}

/*
-Display option menu
*/
void	menu_option(void)
{
	ft_put_image_to_image(_var()->menu->img, _var()->menu->bg,
		(t_vector2D){0, 0});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->logo,
		(t_vector2D){716 - OFFSET_X - 45, 155 - OFFSET_Y + 50});
	draw_bar_fill();
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons[_var()->menu
		->o_state[0].state][_var()->menu->mute_s_state],
		_var()->menu->o_state[0].hitbox[0]);
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons[_var()->menu
		->o_state[1].state][L_ARR], _var()->menu->o_state[1].hitbox[0]);
	ft_put_image_to_image(_var()->menu->img, _var()->menu->bar[EMPTY][BAR_LEFT],
		(t_vector2D){819 - OFFSET_X, 443 - OFFSET_Y});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->bar[EMPTY][BAR_MID],
		(t_vector2D){912 - OFFSET_X, 443 - OFFSET_Y});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->bar[EMPTY]
	[BAR_RIGHT], (t_vector2D){1005 - OFFSET_X, 443 - OFFSET_Y});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons[_var()->menu
		->o_state[2].state][R_ARR], _var()->menu->o_state[2].hitbox[0]);
	menu_bot_options();
}
