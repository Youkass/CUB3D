/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:21:06 by yobougre          #+#    #+#             */
/*   Updated: 2022/12/03 16:54:06 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	recompute_array_shot(int index)
{
	while (index + 1 < _player()->shoot_n)
	{
		_player()->shott[index] = _player()->shott[index + 1];
		index++;
	}
}

void	update_bullets3f(void)
{
	int			i;
	int			new_shoot_n;
	t_vector3F	velo;

	new_shoot_n = _player()->shoot_n;
	i = 0;
	while (i < _player()->shoot_n)
	{
		_player()->shott[i].n++;
		velo = velocity_get_point3f(_player()->shott[i].start_pos,
				_player()->shott[i].velo.velo,
				get_time(_player()->shott[i].start_time));
		if (get_time(_player()->shott[i].start_time)
			>= (float)_player()->shott[i].velo.time_ms)
		{
			new_shoot_n--;
			recompute_array_shot(i);
		}
		else
			_player()->shott[i].pos = velo;
		i++;
	}
	_player()->shoot_n = new_shoot_n;
}

void	set_spectate(void)
{
	int						i;
	static unsigned long	start = 0;

	i = 0;
	if (!start && _player()->is_dead)
		start = get_clock(_var()->clock);
	if (start && _player()->is_dead && _var()->alive[TRED] > 0
		&& _var()->alive[TBLUE] > 0 && _var()->linked_players > 2
		&& get_time(start) > 300000)
	{
		_player()->spectate = 1;
		_player()->spec_id = -1;
		while (i < _var()->linked_players)
		{
			if (_var()->o_player[i].team == _player()->team
				&& _var()->o_player[i].is_dead == 0)
				_player()->spec_id = i;
			i++;
		}
	}
}

static void	ft_call(void)
{
	planet_clock();
	draw_sky();
	check_death();
	death_clock();
	reload_clock();
	draw_rays();
	walk_clock();
	ft_play_music(GAME_MUSIC);
	set_spectate();
}

int	ft_loop(void)
{
	ft_call();
	if ((_var()->is_host == CLIENT || _var()->is_host == SERVER))
		ft_loop_multi();
	if (_player()->is_shooting > 0)
		ft_play_own_shot();
	update_bullets3f();
	bullet_casting();
	hud();
	if (_var()->round_state == ROUND_END_WAIT)
		ft_if_round_end_wait();
	ft_draw_map();
	render_health(pos(50, 250));
	if (_player()->weapon_id != KNIFE)
		ft_is_not_knife();
	if (_player()->is_dead)
		draw_death();
	mlx_put_image_to_window(_mlx()->mlx, _mlx()->mlx_win, _img()->img, 0, 0);
	ft_reload_frame();
	return (0);
}
