/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:05:50 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/07 13:14:20 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	draw_bg(void)
{

	t_int		var;

	var.i = 0;
	while (var.i < WIN_W)
	{
		var.j = 0;
		while (var.j < WIN_H)
		{
			ft_put_pixel_color(&_var()->menu->img, (char [4]){177, 177, 177, 0}, (int)var.i, (int)var.j);
			var.j++;
		}
		var.i++;
	}
}

/*
-Compute the percentage of b in a. 30% {b} of 100 {b} = 30 {result};
*/
int	perc(int a, int b)
{
	return ((a / 100) * b);
}

/*
-Display starting menu
*/
void	menu_start(void)
{
	draw_bg();
	ft_put_image_to_image(_var()->menu->img, _var()->menu->bg,
		(t_vector2D){0, 0});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->logo,
		(t_vector2D){WIN_W / 2 - (_var()->menu->logo.width / 2), perc(WIN_H, 20) - (_var()->menu->logo.height / 2)});
	ft_put_sprite_to_image(_var()->menu->img, _var()->menu->planet,
	(t_vector2D){0, 0}, (t_vector2D){_var()->menu->n * 48, _var()->menu->ny * 48}, (t_vector2D){48, 48});
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons
	[_var()->menu->s_state[0].state][PLAY], _butp()[0]);
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons
	[_var()->menu->s_state[1].state][OPTIONS], _butp()[1]);
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons
	[_var()->menu->s_state[2].state][CREDITS], _butp()[2]);
	ft_put_image_to_image(_var()->menu->img, _var()->menu->buttons
	[_var()->menu->s_state[3].state][EXIT], _butp()[3]);
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
