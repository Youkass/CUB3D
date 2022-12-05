/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:12:42 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/05 17:49:00 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	draw_void(void)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (y < WIN_H / 2 && x < WIN_W)
		{
			ft_put_pixel_color(_img(), _var()->colors[1],
				x, y);
			x++;
		}
		while (y < WIN_H && y > WIN_H / 2 && x < WIN_W)
		{
			ft_put_pixel_color(_img(), _var()->colors[0],
				x, y);
			x++;
		}
		y++;
	}
}

void	ft_init_player_pos(void)
{
	_player()->x = 5;
	_player()->y = 3;
	_player()->angle = 0;
	_ray()->time = 0;
	_ray()->old_time = 0;
	_player()->hb.hit.radius = 0.5;
}

void	ft_print_tab(char **s)
{
	int	i;
	int	line;

	i = 0;
	while (s[i])
	{
		line = ft_strlen(s[i]);
		++i;
	}
	_img()->map_width = line;
	_img()->map_height = i;
}

int	ft_hook(int keycode)
{
	get_key(keycode);
	return (0);
}

int	ft_loop_hook(void)
{
	_player()->dir = (int)round(4 * _player()->angle / (2 * PI) + 8) % 4;
	ft_fps();
	key_hook();
	ft_loop();
	return (0);
}
