/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_casting_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 17:02:24 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/01 17:03:48 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	put_pixel_from_mode(t_obj *player, int stripe, int y)
{
	if (!_var()->tex_mode)
		normal_player(player, stripe, y);
	else if (_var()->tex_mode == 1)
		walking_player(player, stripe, y);
	else
		dead_player(player, stripe, y);
}

void	choose_mode(t_obj *player, t_obj *my_player)
{
	int	dior;
	int	walk;

	dior = mod(normalise_between((t_vector2D){0, 360}, (t_vector2D){0, 16},
				player->angle) + normalise_between((t_vector2D){0, 360},
				(t_vector2D){0, 16}, rad_to_deg(atan2(my_player->y - player->y,
						my_player->x - player->x))), 16);
	walk = mod(normalise_between((t_vector2D){0, 360}, (t_vector2D){0,
				8}, player->angle) + normalise_between((t_vector2D){0, 360},
				(t_vector2D){0, 8}, rad_to_deg(atan2(my_player->y
						- player->y, my_player->x - player->x))), 8);
	_var()->tex_mode = 0;
	_var()->tex_dir = dior;
	if (player->is_walking == 1)
	{
		_var()->tex_mode = 1;
		_var()->walk_tex = walk;
	}
	if (player->is_dead == 1)
		_var()->tex_mode = 2;
}

int	nearest(t_obj *player)
{
	if (compute_distance((t_vector2F){player->x, player->y},
		(t_vector2F){_var()->sort_player[j].x, _var()->sort_player[j]
		.y}) > compute_distance((t_vector2F){player->x, player->y},
			(t_vector2F){_var()->sort_player[i].x, _var()->sort_player
			[i].y}))
		return (1);
	return (0);
}

void	swap_pl(t_obj *player, int i)
{
	t_obj	tmp;

	if (nearest(player))
	{
		tmp = _var()->sort_player[i];
		_var()->sort_player[i] = _var()->sort_player[j];
		_var()->sort_player[j] = tmp;
	}
}

int	compute_distance(t_vector2F a, t_vector2F b)
{
	return ((int)(fabsf(b.x - a.x) + fabsf(b.y - a.y)));
}
