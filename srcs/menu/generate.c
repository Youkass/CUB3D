/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:38:57 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/01 17:24:37 by denissereno      ###   ########.fr       */
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

	if (!path)
	{
		sprite.img = NULL;
		return (sprite);
	}
	sprite.img = mlx_xpm_file_to_image(_mlx()->mlx, path,
			&sprite.w, &sprite.h);
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
	_var()->menu->bar = malloc(sizeof(t_data *) * 2);
	_var()->menu->bar[0] = malloc(sizeof(t_data) * 3);
	_var()->menu->bar[0][0] = generate_image("./img/menu/bar/left_empty.xpm");
	_var()->menu->bar[0][1] = generate_image("./img/menu/bar/mid_empty.xpm");
	_var()->menu->bar[0][2] = generate_image("./img/menu/bar/right_empty.xpm");
	_var()->menu->bar[1] = malloc(sizeof(t_data) * 3);
	_var()->menu->bar[1][0] = generate_image("./img/menu/bar/left_fill.xpm");
	_var()->menu->bar[1][1] = generate_image("./img/menu/bar/mid_fill.xpm");
	_var()->menu->bar[1][2] = generate_image("./img/menu/bar/right_fill.xpm");	
	while (it.y < 2)
	{
		it.x = 0;
		while (it.x < 3)
		{
			if (!_var()->menu->bar[it.y][it.x].img)
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
		butp = malloc(sizeof(t_vector2D) * 4);
		but = perc(WIN_H, 40) - (_var()->menu->buttons[PLAY]->h / 2);
		butp[0] = (t_vector2D){(WIN_W / 2) - (_var()->menu->buttons[PLAY]->w / 2), but};
		but += _var()->menu->buttons[PLAY]->h + perc(WIN_H, 3);
		butp[1] = (t_vector2D){(WIN_W / 2) - (_var()->menu->buttons[PLAY]->w / 2), but};
		but += _var()->menu->buttons[PLAY]->h + perc(WIN_H, 3);
		butp[2] = (t_vector2D){(WIN_W / 2) - (_var()->menu->buttons[PLAY]->w / 2), but};
		but += _var()->menu->buttons[PLAY]->h + perc(WIN_H, 3);
		butp[3] = (t_vector2D){(WIN_W / 2) - (_var()->menu->buttons[PLAY]->w / 2), but};
	}
	return (butp);
}


t_vector2D	*_butpl(void)
{
	static t_vector2D	*butp = NULL;
	int	i;
	int	j;

	i = 3;
	j = 0;
	if (!butp)
	{
		butp = malloc(sizeof(t_vector2D) * 4);
		while (i)
		{
			butp[j] = (t_vector2D){(WIN_W / 2) - (i * 84) + 128, 350};
			i--;
			j++;
		}
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
	_var()->menu->buttons = malloc(sizeof(t_data *) * 3);
	while (it.y < 3)
	{
		_var()->menu->buttons[it.y] = malloc(sizeof(t_data) * 12);
		it.x = 0;
		while (it.x < 12)
		{
			tmp = ft_strjoin(paths[it.y], name[it.x]);
			_var()->menu->buttons[it.y][it.x] = generate_image(tmp);
			if (!_var()->menu->buttons[it.y][it.x].img)
			{
				printf("error image\n");
				return ;
			}
			free(tmp);
			it.x++;
		}
		it.y++;
	}
}

void	gen_serv_but(void)
{
	_var()->menu->nb_p[0][0] = generate_image("./img/menu/serv/2.xpm");
	_var()->menu->nb_p[0][1] = generate_image("./img/menu/serv/2_h.xpm");
	_var()->menu->nb_p[1][0] = generate_image("./img/menu/serv/4.xpm");
	_var()->menu->nb_p[1][1] = generate_image("./img/menu/serv/4_h.xpm");
	_var()->menu->nb_p[2][0] = generate_image("./img/menu/serv/6.xpm");
	_var()->menu->nb_p[2][1] = generate_image("./img/menu/serv/6_h.xpm");
	_var()->menu->nb_p[3][0] = generate_image("./img/menu/serv/join.xpm");
	_var()->menu->nb_p[3][1] = generate_image("./img/menu/serv/join_h.xpm");
}

void	generate_button_state(void)
{
	int					i;
	int					width;
	int					height;
	static t_vector2D	btn[7] = (t_vector2D [7]){{678, 460}, {774, 460},
	{1083, 460}, {678, 560}, {774, 560}, {1083, 560}, {888, 668}};

	width = _var()->menu->buttons[PLAY]->w;
	height =  _var()->menu->buttons[PLAY]->h;
	_var()->menu->s_state = malloc(sizeof(t_button) * 4);
	i = 0;
	while (i < 4)
	{
		_var()->menu->s_state[i].state = 0;
		_var()->menu->s_state[i].hitbox[0] =  _butp()[i];
		_var()->menu->s_state[i].hitbox[1] = (t_vector2D){ _butp()[i].x + width, _butp()[i].y};
		_var()->menu->s_state[i].hitbox[2] = (t_vector2D){_butp()[i].x, _butp()[i].y + height};
		_var()->menu->s_state[i].hitbox[3] =(t_vector2D){_butp()[i].x + width, _butp()[i].y + height};
		i++;
	}
	_var()->menu->o_state = malloc(sizeof(t_button) * 7);
	i = 0;
	while (i < 7)
	{
		_var()->menu->o_state[i].state = 0;
		_var()->menu->o_state[i].hitbox[0] = (t_vector2D){btn[i].x - OFFSET_X,
			btn[i].y - OFFSET_Y};
		_var()->menu->o_state[i].hitbox[1] = (t_vector2D){btn[i].x - OFFSET_X
			+ _var()->menu->buttons[NORMAL][MUTE_S].w , btn[i].y
			- OFFSET_Y};
		_var()->menu->o_state[i].hitbox[2] = (t_vector2D){btn[i].x - OFFSET_X,
			btn[i].y - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].h};
		_var()->menu->o_state[i].hitbox[3] = (t_vector2D){btn[i].x - OFFSET_X,
			btn[i].y - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].w
			+ _var()->menu->buttons[NORMAL][MUTE_S].h};
		i++;
	}
	_var()->menu->p_state = malloc(sizeof(t_button) * 4);
	i = 0;
	width = 64;
	height =  64;
	while (i < 4)
	{
		if (i == 3)
			width = 128;
		_var()->menu->p_state[i].state = 0;
		_var()->menu->p_state[i].hitbox[0] =  _butpl()[i];
		_var()->menu->p_state[i].hitbox[1] = (t_vector2D){ _butpl()[i].x + width, _butpl()[i].y};
		_var()->menu->p_state[i].hitbox[2] = (t_vector2D){_butpl()[i].x, _butpl()[i].y + height};
		_var()->menu->p_state[i].hitbox[3] =(t_vector2D){_butpl()[i].x + width, _butpl()[i].y + height};
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
	_image()->alpha['.'] = generate_image("./img/menu/alpha/dot.xpm");
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
	_var()->menu->pos_m_bar = (t_vector2D){819 - OFFSET_X + 42,
	542 - OFFSET_Y + 36};
	_var()->menu->pos_s_bar = (t_vector2D){819 - OFFSET_X + 42,
	443 - OFFSET_Y + 36};
	_img()->img = mlx_new_image(_mlx()->mlx, WIN_W, WIN_H);
	_img()->addr = mlx_get_data_addr(_img()->img,
	&_img()->bits_per_pixel, &_img()->line_length,& _img()->endian);
	_img()->h = WIN_H;
	_img()->w = WIN_W;
	_var()->menu->mute_m_state = MUTE_M;
	_var()->menu->mute_s_state = MUTE_S;
	_var()->menu->s_bar = 0;
	_var()->menu->m_bar = 0;
	_var()->menu->draging_m = 0;
	_var()->menu->n = 0;
	_var()->menu->ny = 0;
	_var()->menu->start = get_clock(_var()->clock);
	_var()->menu->draging_s = 0;
	_var()->menu->wait = generate_image("./img/menu/wait.xpm");
	_butpl();
	gen_alpha();
	gen_menu_bars();
	gen_menu_buttons();
	generate_button_state();
	gen_serv_but();
	_var()->menu->wall = generate_image("./img/wall.xpm");
	_var()->menu->logo = generate_image("./img/menu/img/logo.xpm");
	if (WIN_W == 1440)
		_var()->menu->bg = generate_image("./img/bg1440.xpm");
	else
		_var()->menu->bg = generate_image("./img/bg1920.xpm");
	_butp();
	_var()->menu->planets[0] = generate_image("./img/spritesheet.xpm");
	_var()->menu->planets[1] = generate_image("./img/ice.xpm");
	if (!_var()->menu->bg.img || !_var()->menu->logo.img)
	{
		printf("image error\n");
		return ;
	}
}
