/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:46:01 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 19:06:27 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	draw_sky(void)
{
	static t_vector2D	pl_coord[2] = {{2000, 500}, {1050, 500}};
	t_vector2D			p;

	p = pos(-1, -1);
	_menu()->draw_pl[0] = p;
	_menu()->draw_pl[1] = p;
	ft_norme_draw_sky(pl_coord);
}

void	pixel_sky(t_int	var, int xo)
{
	t_vector2D	tmp;

	if (var.j < WIN_H / 2 + _player()->pitch)
	{
		tmp = pos(xo, var.j);
		if (var.i == 800 && (var.j + WIN_H / 2)
			- _player()->pitch == 550)
			_menu()->planets_pos[0] = tmp;
		else if (var.i == 200 && (var.j + WIN_H / 2)
			- _player()->pitch == 200)
			_menu()->planets_pos[1] = tmp;
		else
			ft_put_pixel(_img(), &_image()->bg, (t_vector2D){var.i,
				var.j}, (t_vector2D){xo, (var.j + WIN_H / 2)
				- _player()->pitch});
	}
	else
		ft_put_pixel_color(_img(), (char [4]){155, 155, 155, 0},
			var.i, var.j);
}

void	*ft_draw_void(void *r)
{
	t_int		var;
	t_vector2D	start_end;
	int			xo;

	start_end = *(t_vector2D *)r;
	var.i = start_end.x;
	while (var.i < start_end.y)
	{
		var.j = 0;
		while (var.j < WIN_H)
		{
			xo = ((int)_player()->angle * 4) - var.i;
			if (xo < 0)
				xo += WIN_W;
			xo = xo % WIN_W;
			pixel_sky(var, xo);
			var.j++;
		}
		var.i++;
	}
	return (NULL);
}

void	thread_sky(t_vector2D r[10])
{
	int	i;

	i = 0;
	while (i < 10)
	{
		pthread_create(&_var()->th_void[i], NULL, ft_draw_void, &r[i]);
		i++;
	}
	while (i)
		pthread_join(_var()->th_void[i--], NULL);
	if (_menu()->planets_pos[0].x != -1 && _menu()->planets_pos[0].y != -1)
		ft_put_sprite_to_images(_menu()->planets[0], _menu()->planets_pos[0],
			(t_vector2D){_menu()->n * 48,
			_menu()->ny * 48}, (t_vector2D){48, 48});
	if (_menu()->planets_pos[1].x != -1
		&& _menu()->planets_pos[1].y != -1)
		ft_put_sprite_to_images(_menu()->planets[0], _menu()->planets_pos[1],
			(t_vector2D){_menu()->n * 48,
			_menu()->ny * 48}, (t_vector2D){48, 48});
}

void	draw_void_thread(void)
{
	static t_vector2D	r[10];
	static int			started = 0;
	t_vector2D			p;
	int					i;

	p = pos(-1, -1);
	_menu()->planets_pos[0] = p;
	_menu()->planets_pos[1] = p;
	if (!started)
	{
		i = 0;
		while (i < 10)
		{
			r[i] = (t_vector2D){(WIN_W / 10) * i, (WIN_W / 10) * (i + 1)};
			i++;
		}
		started = 1;
	}
	thread_sky(r);
}
