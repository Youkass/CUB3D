/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:41:58 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

void	gen_serv_but(void)
{
	_menu()->nb_p[0][0] = generate_image("./img/menu/serv/host.xpm");
	_menu()->nb_p[0][1] = generate_image("./img/menu/serv/host_h.xpm");
	_menu()->nb_p[0][2] = generate_image("./img/menu/serv/host_ac.xpm");
	_menu()->nb_p[3][0] = generate_image("./img/menu/serv/join.xpm");
	_menu()->nb_p[3][1] = generate_image("./img/menu/serv/join_h.xpm");
	_menu()->nb_p[3][2] = generate_image("./img/menu/serv/join_h.xpm");
}

void	butpl_hitbox(void)
{
	int	width;
	int	height;
	int	i;

	i = 0;
	_menu()->p_state = ft_malloc(sizeof(t_button) * 4);
	width = _menu()->buttons[PLAY]->w;
	height = _menu()->buttons[PLAY]->h;
	while (i < 4)
	{
		if (i == 3)
			width = 128;
		_menu()->p_state[i].state = 0;
		_menu()->p_state[i].hitbox[0] = _butpl()[i];
		_menu()->p_state[i].hitbox[1] = (t_vector2D){_butpl()[i].x + width,
		_butpl()[i].y};
		_menu()->p_state[i].hitbox[2] = (t_vector2D){_butpl()[i].x,
		_butpl()[i].y + height};
		_menu()->p_state[i].hitbox[3] = (t_vector2D){_butpl()[i].x + width,
		_butpl()[i].y + height};
		++i;
	}
}

void	o_state_hitbox(t_vector2D btn[7])
{
	int	i;
	int	w;

	_menu()->o_state = ft_malloc(sizeof(t_button) * 7);
	i = 0;
	w = _menu()->buttons[NORMAL][MUTE_S].w;
	while (i < 7)
	{
		_menu()->o_state[i].state = 0;
		_menu()->o_state[i].hitbox[0] = (t_vector2D){btn[i].x - OFFSET_X,
		btn[i].y - OFFSET_Y};
		_menu()->o_state[i].hitbox[1] = (t_vector2D){btn[i].x - OFFSET_X + w,
		btn[i].y - OFFSET_Y};
		_menu()->o_state[i].hitbox[2] = (t_vector2D){btn[i].x - OFFSET_X,
		btn[i].y - OFFSET_Y + _menu()->buttons[NORMAL][MUTE_S].h};
		_menu()->o_state[i].hitbox[3] = (t_vector2D){btn[i].x - OFFSET_X,
		btn[i].y - OFFSET_Y + _menu()->buttons[NORMAL][MUTE_S].w
		+ _menu()->buttons[NORMAL][MUTE_S].h};
		i++;
	}
}

void	butp_hitbox(void)
{
	int	width;
	int	height;
	int	i;

	width = _menu()->buttons[PLAY]->w;
	height = _menu()->buttons[PLAY]->h;
	_menu()->s_state = ft_malloc(sizeof(t_button) * 4);
	i = 0;
	while (i < 4)
	{
		_menu()->s_state[i].state = 0;
		_menu()->s_state[i].hitbox[0] = _butp()[i];
		_menu()->s_state[i].hitbox[1] = (t_vector2D){_butp()[i].x + width,
		_butp()[i].y};
		_menu()->s_state[i].hitbox[2] = (t_vector2D){_butp()[i].x,
		_butp()[i].y + height};
		_menu()->s_state[i].hitbox[3] = (t_vector2D){_butp()[i].x + width,
		_butp()[i].y + height};
		i++;
	}
}

void	generate_button_state(void)
{
	static t_vector2D	btn[7] = (t_vector2D [7]){{678, 460}, {774, 460},
	{1083, 460}, {678, 560}, {774, 560}, {1083, 560}, {888, 668}};

	butp_hitbox();
	o_state_hitbox(btn);
	butpl_hitbox();
}
