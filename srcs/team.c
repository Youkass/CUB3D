/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   team.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:39:25 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/23 13:53:50 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_player_team(void)
{
	int	i;

	i = 0;
	while (i < _var()->linked_players / 2)
	{
		if (_team()[_player()->team]->players[i] == _player()->id)
		{
			_player()->team_id = i;
			break ;
		}
		i++;
	}
	_player()->x = _team()[_player()->team]->player_spawn[_player()->team_id].x;
	_player()->y = _team()[_player()->team]->player_spawn[_player()->team_id].y;
}

int	get_id_by_pseudo(char *pseudo)
{
	int	i;

	i = 0;
	while (i < _var()->linked_players)
	{
		if (!strcmp(_var()->o_player[i].pseudo, pseudo))
			return (_var()->o_player[i].id);
		i++;
	}
	return (-1);
}

static void	ft_init_team(t_team **team)
{
	team[TEAM_BLUE]->player_spawn[0] = posf(40, 9);
	team[TEAM_BLUE]->player_spawn[1] = posf(40, 10);
	team[TEAM_BLUE]->player_spawn[2] = posf(41, 9);
	team[TEAM_BLUE]->player_spawn[3] = posf(41, 9);
	team[TEAM_BLUE]->player_spawn[4] = posf(41, 9);
	team[TEAM_RED]->player_spawn[0] = posf(3, 3);
	team[TEAM_RED]->player_spawn[1] = posf(3, 4);
	team[TEAM_RED]->player_spawn[2] = posf(3, 2);
	team[TEAM_RED]->player_spawn[3] = posf(3, 3);
	team[TEAM_RED]->player_spawn[4] = posf(3, 3);
	team[TEAM_BLUE]->loose = 0;
	team[TEAM_BLUE]->win = 0;
	team[TEAM_BLUE]->team_spawn = posf(40, 9);
}

void	init_teams(void)
{
	int			i;
	t_team		**team;

	team = _team();
	team[TEAM_RED]->loose = 0;
	team[TEAM_RED]->win = 0;
	team[TEAM_RED]->team_spawn = posf(3, 3);
	ft_init_team(team);
	i = 0;
	while (i < _var()->linked_players / 2)
	{
		team[TEAM_RED]->players[i] = _var()->red[i];
		i++;
	}
	i = 0;
	while (i < _var()->linked_players / 2)
	{
		team[TEAM_BLUE]->players[i] = _var()->blue[i];
		i++;
	}
	init_player_team();
}
