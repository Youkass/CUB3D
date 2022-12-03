/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:26:11 by yobougre          #+#    #+#             */
/*   Updated: 2022/12/03 19:10:35 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	ft_draw_first(void)
{
	int		i;
	t_obj	player;
	t_obj	my_player;

	i = 0;
	while (i < _var()->linked_players / 2)
	{
		player = _var()->o_player[_var()->red[i]];
		if (_player()->spectate && _player()->spec_id >= 0
			&& _player()->spec_id < _var()->linked_players)
			my_player = _var()->o_player[_player()->spec_id];
		else
			my_player = *_player();
		if (player.x >= my_player.x - 8 && player.x <= my_player.x + 8
			&& player.y >= my_player.y - 8 && player.y <= my_player.x + 8)
			drawcircle(ft_return_xp(&player, &my_player),
				ft_return_yp(&player, &my_player),
				ft_return_radius(&player), 0xD2042D);
		i++;
	}
}

static void	ft_draw_next(void)
{
	int		i;
	t_obj	player;
	t_obj	my_player;

	i = 0;
	while (i < _var()->linked_players / 2)
	{
		player = _var()->o_player[_var()->blue[i]];
		if (_player()->spectate && _player()->spec_id >= 0
			&& _player()->spec_id < _var()->linked_players)
			my_player = _var()->o_player[_player()->spec_id];
		else
			my_player = *_player();
		if (player.x >= my_player.x - 8 && player.x <= my_player.x + 8
			&& player.y >= my_player.y - 8 && player.y <= my_player.x + 8)
			drawcircle(ft_return_xp(&player, &my_player),
				ft_return_yp(&player, &my_player),
				ft_return_radius(&player), 0x005b96);
		i++;
	}
}

void	draw_player_map(void)
{
	if ((_var()->is_host == CLIENT || _var()->is_host == SERVER)
		&& _player()->team == TEAM_RED)
		ft_draw_first();
	else if ((_var()->is_host == CLIENT || _var()->is_host == SERVER)
		&& _player()->team == TEAM_BLUE)
		ft_draw_next();
	else
		drawcircle(ft_return_xp(_player(), _player()), ft_return_yp(_player(),
				_player()), ft_return_radius(_player()), 0xD2042D);
}

static void	ft_draw_map_next(t_int var, t_vector2D offset)
{
	if (is_wall(_var()->map[var.i][var.j]))
		ft_draw_wall(offset);
	if (_var()->map[var.i][var.j] == '0')
		ft_draw_floor(offset);
	if (is_player(_var()->map[var.i][var.j]))
		ft_draw_floor(offset);
}

void	ft_draw_map(void)
{
	t_int		var;
	t_vector2D	offset;

	var.i = _player()->y - MINIMAP_SIZE;
	offset = pos(0, 0);
	if (var.i < 0)
		var.i = 0;
	while (var.i < _var()->map_height && var.i < _player()->y + MINIMAP_SIZE)
	{
		var.j = _player()->x - MINIMAP_SIZE;
		if (var.j < 0)
			var.j = 0;
		offset.x = 0;
		while (var.j < _var()->map_width && var.j < _player()->x + MINIMAP_SIZE)
		{
			ft_draw_map_next(var, offset);
			var.j++;
			offset.x++;
		}
		offset.y++;
		var.i++;
	}
	draw_player_map();
	mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win, _img()->img, 0, 0);
}
