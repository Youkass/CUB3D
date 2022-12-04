/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:15:41 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 18:17:16 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	draw_bg(char color[4])
{
	t_int		var;

	var.i = 0;
	while (var.i < WIN_W)
	{
		var.j = 0;
		while (var.j < WIN_H)
		{
			ft_put_pixel_color(_img(), color, (int)var.i, (int)var.j);
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
	static t_vector2D	double_pos[2];
	static int			start = 0;

	if (!start)
	{
		double_pos[1].x = 430;
		double_pos[1].y = 50;
		double_pos[0].x = 722;
		double_pos[0].y = 50;
		++start;
	}
	ft_play_music(MENU_MUSIC);
	draw_bg((char [4]){0, 0, 0, 0});
	ft_put_image_to_image(*_img(), _menu()->bg,
		(t_vector2D){0, 0});
	ft_put_image_to_image(*_img(), _menu()->buttons
	[_menu()->s_state[0].state][PLAY], _butp()[0]);
	ft_put_image_to_image(*_img(), _menu()->buttons
	[_menu()->s_state[1].state][OPTIONS], _butp()[1]);
	ft_put_image_to_image(*_img(), _menu()->buttons
	[_menu()->s_state[2].state][CREDITS], _butp()[2]);
	ft_put_image_to_image(*_img(), _menu()->buttons
	[_menu()->s_state[3].state][EXIT], _butp()[3]);
	ft_end_intro(double_pos);
}

void	menu_player(void)
{
	draw_bg((char [4]){0, 0, 0, 0});
	ft_put_image_to_image(*_img(), _menu()->bg,
		(t_vector2D){0, 0});
	ft_put_img_to_img_scale(*_img(),
		_menu()->logo, (t_vector2D){WIN_W / 2 - (_menu()->logo.w * 2) - 30,
		20}, (t_vector2F){0.15, 0.15});
	ft_put_image_to_image(*_img(),
		_menu()->nb_p[0][_menu()->p_state[0].state], _butpl()[0]);
	ft_put_image_to_image(*_img(),
		_menu()->nb_p[3][_menu()->p_state[3].state], _butpl()[3]);
}

void	ft_draw_lobby(int size_box, t_vector2D size_box_minus)
{
	int	i;

	i = 0;
	while (i < _var()->linked_players)
	{
		if (_var()->o_player[i].team == TEAM_VOID)
			draw_rectangle(pos(WIN_W / 4 - (_menu()->wait.w / 2) + i * size_box,
					(WIN_H / 3) / 2 + 16), size_box_minus,
				(char [4]){0, 0, 0, 100});
		else if (_var()->o_player[i].team == TEAM_RED)
			draw_rectangle(pos(WIN_W / 4 - (_menu()->wait.w / 2) + i * size_box,
					(WIN_H / 3) / 2 + 16), size_box_minus,
				(char [4]){0, 34, 250, 250});
		else
			draw_rectangle(pos(WIN_W / 4 - (_menu()->wait.w / 2) + i * size_box,
					(WIN_H / 3) / 2 + 16), size_box_minus,
				(char [4]){255, 154, 0, 250});
		i++;
	}
}
