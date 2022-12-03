/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   team.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:39:25 by denissereno       #+#    #+#             */
/*   Updated: 2022/12/03 19:17:15 by dasereno         ###   ########.fr       */
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

void	init_teams(void)
{
	int			i;
	t_vector2D	p;

	_team()[TEAM_RED]->loose = 0;
	_team()[TEAM_RED]->win = 0;
	p = pos(3, 3);
	i = 0;
	while (i < _var()->linked_players / 2)
	{
		_team()[TEAM_RED]->players[i] = _var()->red[i];
		_team()[TEAM_RED]->player_spawn[i] = p;
		i++;
	}
	_team()[TEAM_BLUE]->loose = 0;
	_team()[TEAM_BLUE]->win = 0;
	p = pos(40, 9);
	i = 0;
	while (i < _var()->linked_players / 2)
	{
		_team()[TEAM_BLUE]->players[i] = _var()->blue[i];
		_team()[TEAM_BLUE]->player_spawn[i] = p;
		i++;
	}
	init_player_team();
}
