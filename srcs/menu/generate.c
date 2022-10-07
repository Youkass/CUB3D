/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:38:57 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/06 00:09:26 by denissereno      ###   ########.fr       */
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
			&sprite.width, &sprite.height);
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

/*
-Functions to generate all others buttons of the menu.
*/
static void	gen_menu_buttons(void)
{
	static char	*name[12] = {"play.xpm", "options.xpm", "credits.xpm",
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

void	generate_button_state(void)
{
	int					i;
	int					offset;
	static t_vector2D	btn[7] = (t_vector2D [7]){{678, 460}, {774, 460},
	{1083, 460}, {678, 560}, {774, 560}, {1083, 560}, {888, 668}};

	offset = 450;
	_var()->menu->s_state = malloc(sizeof(t_button) * 4);
	i = 0;
	while (i < 4)
	{
		_var()->menu->s_state[i].state = 0;
		_var()->menu->s_state[i].hitbox[0] = (t_vector2D){861 - OFFSET_X,
		offset - OFFSET_Y};
		_var()->menu->s_state[i].hitbox[1] = (t_vector2D){861 - OFFSET_X
		+ _var()->menu->buttons[NORMAL][PLAY].width, offset - OFFSET_Y};
		_var()->menu->s_state[i].hitbox[2] = (t_vector2D){861 - OFFSET_X,
		offset - OFFSET_Y + _var()->menu->buttons[NORMAL][PLAY].height};
		_var()->menu->s_state[i].hitbox[3] = (t_vector2D){861 - OFFSET_X
		+ _var()->menu->buttons[NORMAL][PLAY].width, offset - OFFSET_Y
		+ _var()->menu->buttons[NORMAL][PLAY].height};
		i++;
		offset += 100;	
	}
	_var()->menu->o_state = malloc(sizeof(t_button) * 7);
	i = 0;
	while (i < 7)
	{
		_var()->menu->o_state[i].state = 0;
		_var()->menu->o_state[i].hitbox[0] = (t_vector2D){btn[i].x - OFFSET_X,
			btn[i].y - OFFSET_Y};
		_var()->menu->o_state[i].hitbox[1] = (t_vector2D){btn[i].x - OFFSET_X
			+ _var()->menu->buttons[NORMAL][MUTE_S].width , btn[i].y
			- OFFSET_Y};
		_var()->menu->o_state[i].hitbox[2] = (t_vector2D){btn[i].x - OFFSET_X,
			btn[i].y - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].height};
		_var()->menu->o_state[i].hitbox[3] = (t_vector2D){btn[i].x - OFFSET_X,
			btn[i].y - OFFSET_Y + _var()->menu->buttons[NORMAL][MUTE_S].width
			+ _var()->menu->buttons[NORMAL][MUTE_S].height};
		i++;
	}
}

/*
The following function will generate all images for the menu
*/

void    gen_menu_images(void)
{
	_var()->menu = malloc(sizeof(t_menu));
	_var()->menu->pos_m_bar = (t_vector2D){819 - OFFSET_X + 42,
	542 - OFFSET_Y + 36};
	_var()->menu->pos_s_bar = (t_vector2D){819 - OFFSET_X + 42,
	443 - OFFSET_Y + 36};
	_var()->mode = MENU;
	_var()->menu->img.img = mlx_new_image(_mlx()->mlx, WIN_W, WIN_H);
	_var()->menu->img.addr = mlx_get_data_addr(_var()->menu->img.img,
	&_var()->menu->img.bits_per_pixel, &_var()->menu->img.line_length,
	&_var()->menu->img.endian);
	_var()->menu->img.height = WIN_H;
	_var()->menu->img.width = WIN_W;
	_var()->menu->mode = 0;
	_var()->menu->mute_m_state = MUTE_M;
	_var()->menu->mute_s_state = MUTE_S;
	_var()->menu->s_bar = 0;
	_var()->menu->m_bar = 0;
	_var()->menu->draging_m = 0;
	_var()->menu->draging_s = 0;
	gen_menu_bars();
	gen_menu_buttons();
	generate_button_state();
	_var()->menu->wall = generate_image("./img/wall.xpm");
	_var()->menu->logo = generate_image("./img/menu/img/logo.xpm");
	_var()->menu->bg = generate_image("./img/menu/img/background.xpm");
	if (!_var()->menu->bg.img || !_var()->menu->logo.img)
	{
		printf("image error\n");
		return ;
	}
}