/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:38:57 by denissereno       #+#    #+#             */
/*   Updated: 2022/12/01 17:18:28 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/*
This functions simplify the way to generate image. That verify if the images
couldn't be generated.
*/
t_data	generate_image(char *path)
{
	t_data	sprite;
	t_list	*tmp;
	
	memset(&sprite, 0, sizeof(t_data));
	tmp = _lstimg();
	if (!path)
		return (sprite);
	sprite.img = mlx_xpm_file_to_image(_mlx()->mlx, path,
			&sprite.w, &sprite.h);
	ft_lstadd_back(&tmp, ft_new_node(sprite.img));
	if (!sprite.img)
		return (sprite);
	sprite.addr = mlx_get_data_addr(sprite.img, &sprite.bits_per_pixel,
			&sprite.line_length, &sprite.endian);
	return (sprite);
}

/*
-Function that generate the sound and music bar sprites.
*/
static void	gen_menu_bars(void)
{
	t_vector2D	it;

	it = (t_vector2D){0, 0};
	_menu()->bar = ft_malloc(sizeof(t_data *) * 2);
	_menu()->bar[0] = ft_malloc(sizeof(t_data) * 3);
	_menu()->bar[0][0] = generate_image("./img/menu/bar/left_empty.xpm");
	_menu()->bar[0][1] = generate_image("./img/menu/bar/mid_empty.xpm");
	_menu()->bar[0][2] = generate_image("./img/menu/bar/right_empty.xpm");
	_menu()->bar[1] = ft_malloc(sizeof(t_data) * 3);
	_menu()->bar[1][0] = generate_image("./img/menu/bar/left_fill.xpm");
	_menu()->bar[1][1] = generate_image("./img/menu/bar/mid_fill.xpm");
	_menu()->bar[1][2] = generate_image("./img/menu/bar/right_fill.xpm");	
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
	int	but;

	if (!butp)
	{
		butp = ft_malloc(sizeof(t_vector2D) * 4);
		but = perc(WIN_H, 40) - (_menu()->buttons[PLAY]->h / 2);
		butp[0] = (t_vector2D){(WIN_W / 2) - (_menu()->buttons[PLAY]->w / 2), but};
		but += _menu()->buttons[PLAY]->h + perc(WIN_H, 3);
		butp[1] = (t_vector2D){(WIN_W / 2) - (_menu()->buttons[PLAY]->w / 2), but};
		but += _menu()->buttons[PLAY]->h + perc(WIN_H, 3);
		butp[2] = (t_vector2D){(WIN_W / 2) - (_menu()->buttons[PLAY]->w / 2), but};
		but += _menu()->buttons[PLAY]->h + perc(WIN_H, 3);
		butp[3] = (t_vector2D){(WIN_W / 2) - (_menu()->buttons[PLAY]->w / 2), but};
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

/*
-Functions to generate all others buttons of the menu.
*/
static void	gen_menu_buttons(void)
{
	static char	*name[12] = {"solo.xpm", "multi.xpm", "options.xpm",
		"exit.xpm", "restart.xpm", "quit.xpm", "mute_m.xpm", "mute_s.xpm",
		"music.xpm", "sound.xpm", "l_arr.xpm", "r_arr.xpm"};
	static char	*paths[3] = {"./img/menu/btns/nm/", "./img/menu/btns/hv/",
		"./img/menu/btns/ac/"};
	char		*tmp;
	t_vector2D	it;

	it = (t_vector2D){0, 0};
	_menu()->buttons = ft_malloc(sizeof(t_data *) * 3);
	while (it.y < 3)
	{
		_menu()->buttons[it.y] = ft_malloc(sizeof(t_data) * 12);
		it.x = 0;
		while (it.x < 12)
		{
			tmp = ft_strjoin(paths[it.y], name[it.x]);
			_menu()->buttons[it.y][it.x] = generate_image(tmp);
			if (!_menu()->buttons[it.y][it.x].img)
			{
				printf("error image\n");
				return ;
			}
			//free(tmp);
			//tmp = NULL;
			it.x++;
		}
		it.y++;
	}
}

void	gen_serv_but(void)
{
	_menu()->nb_p[0][0] = generate_image("./img/menu/serv/host.xpm");
	_menu()->nb_p[0][1] = generate_image("./img/menu/serv/host_h.xpm");
	_menu()->nb_p[0][2] = generate_image("./img/menu/serv/host_ac.xpm");
	_menu()->nb_p[3][0] = generate_image("./img/menu/serv/join.xpm");
	_menu()->nb_p[3][1] = generate_image("./img/menu/serv/join_h.xpm");
	_menu()->nb_p[3][2] = generate_image("./img/menu/serv/join_h.xpm");
}

void	generate_button_state(void)
{
	int					i;
	int					width;
	int					height;
	static t_vector2D	btn[7] = (t_vector2D [7]){{678, 460}, {774, 460},
	{1083, 460}, {678, 560}, {774, 560}, {1083, 560}, {888, 668}};

	width = _menu()->buttons[PLAY]->w;
	height =  _menu()->buttons[PLAY]->h;
	_menu()->s_state = ft_malloc(sizeof(t_button) * 4);
	i = 0;
	while (i < 4)
	{
		_menu()->s_state[i].state = 0;
		_menu()->s_state[i].hitbox[0] =  _butp()[i];
		_menu()->s_state[i].hitbox[1] = (t_vector2D){ _butp()[i].x + width, _butp()[i].y};
		_menu()->s_state[i].hitbox[2] = (t_vector2D){_butp()[i].x, _butp()[i].y + height};
		_menu()->s_state[i].hitbox[3] =(t_vector2D){_butp()[i].x + width, _butp()[i].y + height};
		i++;
	}
	_menu()->o_state = ft_malloc(sizeof(t_button) * 7);
	i = 0;
	while (i < 7)
	{
		_menu()->o_state[i].state = 0;
		_menu()->o_state[i].hitbox[0] = (t_vector2D){btn[i].x - OFFSET_X,
			btn[i].y - OFFSET_Y};
		_menu()->o_state[i].hitbox[1] = (t_vector2D){btn[i].x - OFFSET_X
			+ _menu()->buttons[NORMAL][MUTE_S].w , btn[i].y
			- OFFSET_Y};
		_menu()->o_state[i].hitbox[2] = (t_vector2D){btn[i].x - OFFSET_X,
			btn[i].y - OFFSET_Y + _menu()->buttons[NORMAL][MUTE_S].h};
		_menu()->o_state[i].hitbox[3] = (t_vector2D){btn[i].x - OFFSET_X,
			btn[i].y - OFFSET_Y + _menu()->buttons[NORMAL][MUTE_S].w
			+ _menu()->buttons[NORMAL][MUTE_S].h};
		i++;
	}
	_menu()->p_state = ft_malloc(sizeof(t_button) * 4);
	i = 0;
	width = _menu()->buttons[PLAY]->w;
	height =  _menu()->buttons[PLAY]->h;
	while (i < 4)
	{
		if (i == 3)
			width = 128;
		_menu()->p_state[i].state = 0;
		_menu()->p_state[i].hitbox[0] =  _butpl()[i];
		_menu()->p_state[i].hitbox[1] = (t_vector2D){ _butpl()[i].x + width, _butpl()[i].y};
		_menu()->p_state[i].hitbox[2] = (t_vector2D){_butpl()[i].x, _butpl()[i].y + height};
		_menu()->p_state[i].hitbox[3] =(t_vector2D){_butpl()[i].x + width, _butpl()[i].y + height};
		i++;
	}
}

void	gen_alpha(void)
{
	int	i;

	i = 65;
	while (i <= 90)
	{
		_image()->alpha[i] = generate_image(ft_strjoin(ft_strjoin("./img/menu/alpha/", (char [2]){i, 0}), ".xpm"));
		i++;
	}
	i = 48;
	while (i <= 57)
	{
		_image()->alpha[i] = generate_image(ft_strjoin(ft_strjoin("./img/menu/alpha/", (char [2]){i, 0}), ".xpm"));
		i++;
	}
	_image()->alpha['_'] = generate_image("./img/menu/alpha/_.xpm");
	_image()->alpha['-'] = generate_image("./img/menu/alpha/-.xpm");
	_image()->alpha['/'] = generate_image("./img/menu/alpha/slash.xpm");
	_image()->alpha['.'] = generate_image("./img/menu/alpha/dot.xpm");
	_image()->alpha[':'] = generate_image("./img/menu/alpha/ddot.xpm");
	_image()->alpha['('] = generate_image("./img/menu/alpha/(.xpm");
	_image()->alpha[')'] = generate_image("./img/menu/alpha/).xpm");
	_image()->alpha[':'] = generate_image("./img/menu/alpha/:.xpm");
	_image()->alpha['\''] = generate_image("./img/menu/alpha/'.xpm");
}

/*
The following function will generate all images for the menu
*/

void    gen_menu_images(void)
{
	_menu()->pos_m_bar = (t_vector2D){819 - OFFSET_X + 42,
	542 - OFFSET_Y + 36};
	_menu()->pos_s_bar = (t_vector2D){819 - OFFSET_X + 42,
	443 - OFFSET_Y + 36};
	_menu()->mute_m_state = MUTE_M;
	_menu()->mute_s_state = MUTE_S;
	_menu()->s_bar = 0;
	_menu()->m_bar = 0;
	_menu()->draging_m = 0;
	_menu()->n = 0;
	_menu()->ny = 0;
	_menu()->start = get_clock(_var()->clock);
	_menu()->draging_s = 0;
	_menu()->wait = generate_image("./img/menu/wait.xpm");
	_butpl();
	gen_alpha();
	gen_menu_bars();
	gen_menu_buttons();
	generate_button_state();
	gen_serv_but();
	_menu()->wall = generate_image("./img/wall.xpm");
	_menu()->logo = generate_image("./img/intro/logo.xpm");
	if (WIN_W == 1440)
		_menu()->bg = generate_image("./img/bg1440.xpm");
	else
		_menu()->bg = generate_image("./img/bg1920.xpm");
	_butp();
	_menu()->planets[0] = generate_image("./img/spritesheet.xpm");
	_menu()->planets[1] = generate_image("./img/ice.xpm");
	if (!_menu()->bg.img || !_menu()->logo.img)
	{
		printf("image error\n");
		return ;
	}
}
