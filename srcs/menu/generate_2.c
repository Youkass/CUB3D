/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:41:58 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 17:43:40 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/*
-Function that generate the sound and music bar sprites.
*/
void	gen_menu_bars(void)
{
	t_vector2D	it;

	it = (t_vector2D){0, 0};
	gen_bar();
	while (it.y < 2)
	{
		it.x = 0;
		while (it.x < 3)
		{
			if (!_menu()->bar[it.y][it.x].img)
			{
				printf("error image\n");
				return ;
			}
			it.x++;
		}
		it.y++;
	}
}

t_vector2D	*_butp(void)
{
	static t_vector2D	*butp = NULL;
	int					but;

	if (!butp)
	{
		butp = ft_malloc(sizeof(t_vector2D) * 4);
		but = perc(WIN_H, 40) - (_menu()->buttons[PLAY]->h / 2);
		butp[0] = (t_vector2D){(WIN_W / 2)
			- (_menu()->buttons[PLAY]->w / 2), but};
		but += _menu()->buttons[PLAY]->h + perc(WIN_H, 3);
		butp[1] = (t_vector2D){(WIN_W / 2)
			- (_menu()->buttons[PLAY]->w / 2), but};
		but += _menu()->buttons[PLAY]->h + perc(WIN_H, 3);
		butp[2] = (t_vector2D){(WIN_W / 2)
			- (_menu()->buttons[PLAY]->w / 2), but};
		but += _menu()->buttons[PLAY]->h + perc(WIN_H, 3);
		butp[3] = (t_vector2D){(WIN_W / 2)
			- (_menu()->buttons[PLAY]->w / 2), but};
	}
	return (butp);
}

t_vector2D	*_butpl(void)
{
	static t_vector2D	*butp = NULL;

	if (!butp)
	{
		butp = ft_malloc(sizeof(t_vector2D) * 4);
		butp[0] = (t_vector2D){(WIN_W / 2) - 64, 350};
		butp[3] = (t_vector2D){(WIN_W / 2) - 64, 450};
	}
	return (butp);
}

static void	while_menu_gen(t_vector2D *it, char	*name[12], char	*paths[3])
{
	char	*tmp;

	it->x = 0;
	while (it->x < 12)
	{
		tmp = ft_strjoin(paths[it->y], name[it->x]);
		_menu()->buttons[it->y][it->x] = generate_image(tmp);
		if (!_menu()->buttons[it->y][it->x].img)
		{
			printf("error image\n");
			return ;
		}
		it->x++;
	}
}

/*
-Functions to generate all others buttons of the menu.
*/
void	gen_menu_buttons(void)
{
	static char	*name[12] = {"solo.xpm", "multi.xpm", "options.xpm",
		"exit.xpm", "restart.xpm", "quit.xpm", "mute_m.xpm", "mute_s.xpm",
		"music.xpm", "sound.xpm", "l_arr.xpm", "r_arr.xpm"};
	static char	*paths[3] = {"./img/menu/btns/nm/", "./img/menu/btns/hv/",
		"./img/menu/btns/ac/"};
	t_vector2D	it;

	it = (t_vector2D){0, 0};
	_menu()->buttons = ft_malloc(sizeof(t_data *) * 3);
	while (it.y < 3)
	{
		_menu()->buttons[it.y] = ft_malloc(sizeof(t_data) * 12);
		it.x = 0;
		while_menu_gen(&it, name, paths);
		it.y++;
	}
}
