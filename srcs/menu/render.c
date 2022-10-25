/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:05:50 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/25 13:02:42 by yobougre         ###   ########.fr       */
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
	draw_bg((char [4]){0, 0, 0, 0});
	ft_put_image_to_image(*_img(), _var()->menu->bg,
		(t_vector2D){0, 0});
	ft_put_image_to_image(*_img(), _var()->menu->logo,
		(t_vector2D){WIN_W / 2 - (_var()->menu->logo.width / 2), perc(WIN_H, 20) - (_var()->menu->logo.height / 2)});
	ft_put_sprite_to_image(*_img(), _var()->menu->planet,
	(t_vector2D){0, 0}, (t_vector2D){_var()->menu->n * 48, _var()->menu->ny * 48}, (t_vector2D){48, 48});
	ft_put_image_to_image(*_img(), _var()->menu->buttons
	[_var()->menu->s_state[0].state][PLAY], _butp()[0]);
	ft_put_image_to_image(*_img(), _var()->menu->buttons
	[_var()->menu->s_state[1].state][OPTIONS], _butp()[1]);
	ft_put_image_to_image(*_img(), _var()->menu->buttons
	[_var()->menu->s_state[2].state][CREDITS], _butp()[2]);
	ft_put_image_to_image(*_img(), _var()->menu->buttons
	[_var()->menu->s_state[3].state][EXIT], _butp()[3]);
}

void	menu_player(void)
{
	draw_bg((char [4]){0, 0, 0, 0});
	ft_put_image_to_image(*_img(), _var()->menu->bg,
		(t_vector2D){0, 0});
	ft_put_image_to_image(*_img(), _var()->menu->logo,
		(t_vector2D){WIN_W / 2 - (_var()->menu->logo.width / 2), perc(WIN_H, 20) - (_var()->menu->logo.height / 2)});

	ft_put_image_to_image(*_img(), _var()->menu->nb_p[0][_var()->menu->p_state[0].state], _butpl()[0]);
	ft_put_image_to_image(*_img(), _var()->menu->nb_p[1][_var()->menu->p_state[1].state],  _butpl()[1]);
	ft_put_image_to_image(*_img(), _var()->menu->nb_p[2][_var()->menu->p_state[2].state],  _butpl()[2]);
	ft_put_image_to_image(*_img(), _var()->menu->nb_p[3][_var()->menu->p_state[3].state],  _butpl()[3]);
}

void	menu_lobby(void)
{
	int	i;

	draw_bg((char [4]){250, 200, 0, 0});
	ft_put_image_to_image(*_img(), _var()->menu->wait,
		(t_vector2D){WIN_W / 2 - (_var()->menu->wait.width / 2), perc(WIN_H, 20) - (_var()->menu->wait.height / 2)});
	i = 0;
	while (i < _var()->linked_players)
	{
		draw_text(_var()->o_player[i].pseudo, (t_vector2D){200, 300 + i * 60}, _img());
		i++;
	}
	if (_img()->is_host == SERVER)
		draw_text(ft_get_host_ip(), (t_vector2D){200, 10}, _img());
	else
		draw_text(_var()->ip, (t_vector2D){200, 10}, _img());
	if (_img()->is_host == SERVER && _var()->linked_players >= _img()->nb_player)
		draw_text("'Space' to start", (t_vector2D){200, 300 + (i + 2) * 60}, _img());
}

void	menu_pseudo(void)
{
	draw_bg((char [4]){250, 200, 0, 0});
	ft_put_image_to_image(*_img(), _var()->alpha['D'], (t_vector2D){300, 300});
	draw_text("Enter your pseudo (max 16)", (t_vector2D){200, 100}, _img());
	draw_rectange((t_vector2D){300, 300}, (t_vector2D){50 * 16, 150}, _img(), (char [4]){0, 0, 0, 0});
	draw_text(_player()->pseudo, (t_vector2D){350, 350}, _img());
}

void	menu_ip(void)
{

	draw_bg((char [4]){250, 200, 0, 0});
	draw_text("Enter your ip (max 15)('space for '.')", (t_vector2D){100, 100}, _img());
	draw_rectange((t_vector2D){300, 300}, (t_vector2D){50 * 16, 150}, _img(), (char [4]){0, 0, 0, 0});
	draw_text(_var()->ip, (t_vector2D){350, 350}, _img());
}


/*
-Display bottoms button of menu_options.
*/
static void	menu_bot_options(void)
{
	ft_put_image_to_image(*_img(), _var()->menu->buttons[_var()
		->menu->o_state[3].state][_var()->menu->mute_m_state],
		_var()->menu->o_state[3].hitbox[0]);
	ft_put_image_to_image(*_img(), _var()->menu->buttons[_var()->menu
		->o_state[4].state][L_ARR], _var()->menu->o_state[4].hitbox[0]);
	ft_put_image_to_image(*_img(), _var()->menu->bar[EMPTY][BAR_LEFT],
		(t_vector2D){819 - OFFSET_X, 542 - OFFSET_Y});
	ft_put_image_to_image(*_img(), _var()->menu->bar[EMPTY][BAR_MID],
		(t_vector2D){912 - OFFSET_X, 542 - OFFSET_Y});
	ft_put_image_to_image(*_img(), _var()->menu->bar[EMPTY]
	[BAR_RIGHT], (t_vector2D){1005 - OFFSET_X, 542 - OFFSET_Y});
	ft_put_image_to_image(*_img(), _var()->menu->buttons[_var()->menu
		->o_state[5].state][R_ARR], _var()->menu->o_state[5].hitbox[0]);
	ft_put_image_to_image(*_img(), _var()->menu->buttons[_var()->menu
		->o_state[6].state][QUIT], _var()->menu->o_state[6].hitbox[0]);
}

/*
-Display option menu
*/
void	menu_option(void)
{
	ft_put_image_to_image(*_img(), _var()->menu->bg,
		(t_vector2D){0, 0});
	ft_put_image_to_image(*_img(), _var()->menu->logo,
		(t_vector2D){716 - OFFSET_X - 45, 155 - OFFSET_Y + 50});
	draw_bar_fill();
	ft_put_image_to_image(*_img(), _var()->menu->buttons[_var()->menu
		->o_state[0].state][_var()->menu->mute_s_state],
		_var()->menu->o_state[0].hitbox[0]);
	ft_put_image_to_image(*_img(), _var()->menu->buttons[_var()->menu
		->o_state[1].state][L_ARR], _var()->menu->o_state[1].hitbox[0]);
	ft_put_image_to_image(*_img(), _var()->menu->bar[EMPTY][BAR_LEFT],
		(t_vector2D){819 - OFFSET_X, 443 - OFFSET_Y});
	ft_put_image_to_image(*_img(), _var()->menu->bar[EMPTY][BAR_MID],
		(t_vector2D){912 - OFFSET_X, 443 - OFFSET_Y});
	ft_put_image_to_image(*_img(), _var()->menu->bar[EMPTY]
	[BAR_RIGHT], (t_vector2D){1005 - OFFSET_X, 443 - OFFSET_Y});
	ft_put_image_to_image(*_img(), _var()->menu->buttons[_var()->menu
		->o_state[2].state][R_ARR], _var()->menu->o_state[2].hitbox[0]);
	menu_bot_options();
}
