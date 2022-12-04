/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:38:57 by denissereno       #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

static void	gen_alphanum_image(void)
{
	int		i;
	char	*str;

	i = 65;
	while (i <= 90)
	{
		str = ft_strjoin(ft_strjoin("./img/menu/alpha/",
					(char [2]){i, 0}), ".xpm");
		_image()->alpha[i] = generate_image(str);
		i++;
	}
	i = 48;
	while (i <= 57)
	{
		str = ft_strjoin(ft_strjoin("./img/menu/alpha/", (char [2]){i, 0}),
				".xpm");
		_image()->alpha[i] = generate_image(str);
		++i;
	}
}

void	gen_alpha(void)
{
	gen_alphanum_image();
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

static void	gen_data_dragbar(void)
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
}

void	gen_bgs(void)
{
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

void	gen_menu_images(void)
{
	gen_data_dragbar();
	_butpl();
	gen_alpha();
	gen_menu_bars();
	gen_menu_buttons();
	generate_button_state();
	gen_serv_but();
	gen_bgs();
}
