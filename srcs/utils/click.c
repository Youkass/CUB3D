/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 00:53:24 by dasereno          #+#    #+#             */
/*   Updated: 2022/11/23 14:10:48 by yobougre         ###   ########.fr       */
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

static void	ft_replace_player(t_obj *player)
{
	double dist;

	player->shoot_n = 0;
	player->z = 0;
	player->dx = -1;
	player->shooted.id = -1;
	player->shooted.shoot = 0;
	player->dy = 0;
	player->is_dead = 0;
	player->is_crouching = 0;
	player->death_n = 0;
	player->plane = (t_vector2F){0, -0.66};
	player->pitch = 0;
	player->norm_pitch = 0;
	dist = hypot(player->dx, player->dy);
	player->angle = 360 - acos(player->dx / dist) * 180 / M_PI;
	player->is_walking = 0;
	player->spectate = 0;
	player->spec_id = -1;
}

void	replace_player(void)
{
	int		i;
	t_obj	*player;

	i = 0;
	player = _player();
	player->is_start = 0;
	_log()->log = NULL;
	_var()->alive[TRED] = _var()->nb_player / 2;
	_var()->alive[TBLUE] = _var()->nb_player / 2;
	memset(player->kill_round, 0, sizeof(player->kill_round));
	player->nr = 0;
	player->nm = 0;
	player->is_shooting = 0;
	player->can_shoot = 1;
	player->start_reload = get_clock(_var()->clock);
	player->health = 100;
	i = 0;
	while (i < NB_WEAPONS)
	{
		player->ammo[i] = _weapon()[i]->ammo;
		player->full_ammo[i] = _weapon()[i]->full_ammo;
		i++;
	}
	ft_replace_player(player);
}

static void	ft_restart_player(t_obj *player)
{
	double	dist;

	_var()->alive[TRED] = _var()->nb_player / 2;
	_var()->alive[TBLUE] = _var()->nb_player / 2;
	memset(&player->kill_match, 0, sizeof(player->kill_match));
	player->nr = 0;
	_var()->match_finished = 0;
	player->kills = 0;
	player->deaths = 0;
	player->nr = 0;
	player->nm = 0;
	player->is_shooting = 0;
	player->can_shoot = 1;
	player->start_reload = get_clock(_var()->clock);
	player->health = 100;
	player->shoot_n = 0;
	player->z = 0;
	player->dx = -1;
	player->shooted.id = -1;
	player->shooted.shoot = 0;
	player->dy = 0;
	player->is_dead = 0;
	player->is_crouching = 0;
	player->death_n = 0;
	player->plane = (t_vector2F){0, -0.66};
	player->pitch = 0;
	player->norm_pitch = 0;
	dist = hypot(player->dx, player->dy);
	player->angle = 360 - acos(player->dx / dist) * 180 / M_PI;
	player->is_walking = 0;
	player->spectate = 0;
	player->spec_id = -1;
}

void	restart_player(void)
{
	int		i;
	t_obj	*player;

	i = 0;
	player = _player();
	while (i < 4)
	{
		_menu()->s_state[i].state = 0;
		i++;
	}
	player->is_start = 0;
	_log()->log = NULL;
	memset(player->kill_round, 0, sizeof(player->kill_round));
	i = 0;
	while (i < NB_WEAPONS)
	{
		player->ammo[i] = _weapon()[i]->ammo;
		player->full_ammo[i] = _weapon()[i]->full_ammo;
		i++;
	}
	ft_restart_player(player);
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
