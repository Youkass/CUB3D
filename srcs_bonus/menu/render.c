/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:05:50 by denissereno       #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

void	menu_leaderboard(void)
{
	int	i;

	draw_leaderboard();
	sort_team();
	i = 0;
	while (i < _var()->n_red)
	{
		draw_pseudo_box_leader(_var()->o_player[_var()->red[i]].pseudo,
			_var()->red[i], i, TEAM_RED);
		i++;
	}
	i = 0;
	while (i < _var()->n_blue)
	{
		draw_pseudo_box_leader(_var()->o_player[_var()->blue[i]].pseudo,
			_var()->blue[i], i, TEAM_BLUE);
		i++;
	}
	if (_player()->id == 0)
		draw_text_scale("press (Maj) to restart", pos(WIN_W / 2 - 462,
				WIN_H - 150), pos(2, 2), (char [4]){238, 238, 238, 250});
}

void	menu_pseudo(void)
{
	draw_bg((char [4]){250, 200, 0, 0});
	ft_put_image_to_image(*_img(), _image()->alpha['D'],
		(t_vector2D){300, 300});
	draw_text("Enter your pseudo (max 16)", (t_vector2D){200, 100},
		(char [4]){238, 238, 238, 250});
	draw_rectangle((t_vector2D){300, 300},
		(t_vector2D){50 * 16, 150}, (char [4]){0, 0, 0, 0});
	draw_text(_player()->pseudo, (t_vector2D){350, 350},
		(char [4]){238, 238, 238, 250});
}

void	menu_ip(void)
{
	draw_bg((char [4]){250, 200, 0, 0});
	draw_text("Enter your ip (max 15)('space for '.')",
		(t_vector2D){100, 100}, (char [4]){238, 238, 238, 250});
	draw_rectangle((t_vector2D){300, 300},
		(t_vector2D){50 * 16, 150}, (char [4]){0, 0, 0, 0});
	draw_text(_var()->ip, (t_vector2D){350, 350},
		(char [4]){238, 238, 238, 250});
}

/*
-Display bottoms button of menu_options.
*/
static void	menu_bot_options(void)
{
	ft_put_image_to_image(*_img(), _menu()->buttons[_var()
		->menu->o_state[3].state][_menu()->mute_m_state],
		_menu()->o_state[3].hitbox[0]);
	ft_put_image_to_image(*_img(), _menu()->buttons[_menu()
		->o_state[4].state][L_ARR], _menu()->o_state[4].hitbox[0]);
	ft_put_image_to_image(*_img(), _menu()->bar[EMPTY][BAR_LEFT],
		(t_vector2D){819 - OFFSET_X, 542 - OFFSET_Y});
	ft_put_image_to_image(*_img(), _menu()->bar[EMPTY][BAR_MID],
		(t_vector2D){912 - OFFSET_X, 542 - OFFSET_Y});
	ft_put_image_to_image(*_img(), _menu()->bar[EMPTY]
	[BAR_RIGHT], (t_vector2D){1005 - OFFSET_X, 542 - OFFSET_Y});
	ft_put_image_to_image(*_img(), _menu()->buttons[_menu()
		->o_state[5].state][R_ARR], _menu()->o_state[5].hitbox[0]);
	ft_put_image_to_image(*_img(), _menu()->buttons[_menu()
		->o_state[6].state][QUIT], _menu()->o_state[6].hitbox[0]);
}

/*
-Display option menu
*/
void	menu_option(void)
{
	ft_put_image_to_image(*_img(), _menu()->bg,
		(t_vector2D){0, 0});
	ft_put_image_to_image(*_img(), _menu()->logo,
		(t_vector2D){716 - OFFSET_X - 45, 155 - OFFSET_Y + 50});
	draw_bar_fill();
	ft_put_image_to_image(*_img(), _menu()->buttons[_menu()
		->o_state[0].state][_menu()->mute_s_state],
		_menu()->o_state[0].hitbox[0]);
	ft_put_image_to_image(*_img(), _menu()->buttons[_menu()
		->o_state[1].state][L_ARR], _menu()->o_state[1].hitbox[0]);
	ft_put_image_to_image(*_img(), _menu()->bar[EMPTY][BAR_LEFT],
		(t_vector2D){819 - OFFSET_X, 443 - OFFSET_Y});
	ft_put_image_to_image(*_img(), _menu()->bar[EMPTY][BAR_MID],
		(t_vector2D){912 - OFFSET_X, 443 - OFFSET_Y});
	ft_put_image_to_image(*_img(), _menu()->bar[EMPTY]
	[BAR_RIGHT], (t_vector2D){1005 - OFFSET_X, 443 - OFFSET_Y});
	ft_put_image_to_image(*_img(), _menu()->buttons[_menu()
		->o_state[2].state][R_ARR], _menu()->o_state[2].hitbox[0]);
	menu_bot_options();
}
