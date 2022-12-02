/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 00:53:24 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/02 14:34:49 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	click(void)
{
	_var()->start_click = get_clock(_var()->clock);
	_var()->click = 1;
}

int	click_update(void)
{
	if (_var()->click && get_time(_var()->start_click) > 170000)
		_var()->click = 0;
	return (0);
}

int	click_delay(void)
{
	if (_var()->click == 1)
		return (1);
	return (0);
}

static void	ft_replace_player(void)
{
	int	i;

	_player()->is_start = 0;
	_log()->log = NULL;
	_var()->alive[TRED] = _var()->nb_player / 2;
	_var()->alive[TBLUE] = _var()->nb_player / 2;
	memset(_player()->kill_round, 0, sizeof(_player()->kill_round));
	_player()->nr = 0;
	_player()->nm = 0;
	_player()->is_shooting = 0;
	_player()->can_shoot = 1;
	_player()->start_reload = get_clock(_var()->clock);
	_player()->health = 100;
	i = 0;
	while (i < NB_WEAPONS)
	{
		_player()->ammo[i] = _weapon()[i]->ammo;
		_player()->full_ammo[i] = _weapon()[i]->full_ammo;
		i++;
	}
}

void	replace_player(void)
{
	int			dist;
	t_vector2F	plane;

	ft_replace_player();
	_player()->shoot_n = 0;
	_player()->z = 0;
	_player()->dx = -1;
	_player()->shooted.id = -1;
	_player()->shooted.shoot = 0;
	_player()->dy = 0;
	_player()->is_dead = 0;
	_player()->is_crouching = 0;
	_player()->death_n = 0;
	plane = posf(0.01, -0.66);
	_player()->plane = plane;
	_player()->pitch = 0;
	_player()->norm_pitch = 0;
	dist = hypot(_player()->dx, _player()->dy);
	_player()->angle = 360 - acos(_player()->dx / dist) * 180 / M_PI;
	_player()->is_walking = 0;
	_player()->spectate = 0;
	_player()->spec_id = -1;
}

static void	ft_restart_player(void)
{
	_player()->is_start = 0;
	_log()->log = NULL;
	_var()->alive[TRED] = _var()->nb_player / 2;
	_var()->alive[TBLUE] = _var()->nb_player / 2;
	memset(&_player()->kill_match, 0, sizeof(_player()->kill_match));
	_player()->nr = 0;
	_var()->match_finished = 0;
	_player()->kills = 0;
	_player()->deaths = 0;
	memset(_player()->kill_round, 0, sizeof(_player()->kill_round));
	_player()->nr = 0;
	_player()->nm = 0;
	_player()->is_shooting = 0;
	_player()->can_shoot = 1;
	_player()->start_reload = get_clock(_var()->clock);
	_player()->health = 100;
	_player()->shoot_n = 0;
	_player()->z = 0;
	_player()->dx = -1;
	_player()->shooted.id = -1;
	_player()->shooted.shoot = 0;
	_player()->dy = 0;
	_player()->is_dead = 0;
	_player()->is_crouching = 0;
	_player()->death_n = 0;
}

static void	ft_restart_next(void)
{
	t_vector2F	plane;
	double		dist;

	plane = posf(0.01, -0.66);
	_player()->plane = plane;
	_player()->pitch = 0;
	_player()->norm_pitch = 0;
	dist = hypot(_player()->dx, _player()->dy);
	_player()->angle = 360 - acos(_player()->dx / dist) * 180 / M_PI;
	_player()->is_walking = 0;
	_player()->spectate = 0;
	_player()->spec_id = -1;
}

void	restart_player(void)
{
	int			i;

	i = 0;
	while (i < 4)
	{
		_menu()->s_state[i].state = 0;
		i++;
	}
	i = 0;
	while (i < NB_WEAPONS)
	{
		_player()->ammo[i] = _weapon()[i]->ammo;
		_player()->full_ammo[i] = _weapon()[i]->full_ammo;
		i++;
	}
	ft_restart_player();
	ft_restart_next();
}

int	is_neutral(void)
{
	int	i;
	int	nb[2];

	i = 0;
	nb[0] = 0;
	nb[1] = 0;
	while (i < _var()->linked_players)
	{
		if (_var()->o_player[i].team == TEAM_VOID)
			return (0);
		else if (_var()->o_player[i].team == TEAM_BLUE)
			nb[0]++;
		else
			nb[1]++;
		i++;
	}
	if (!(_var()->linked_players % 2) && nb[0] == nb[1])
		return (1);
	return (0);
}
