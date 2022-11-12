/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   team.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:39:25 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/12 10:05:57 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_player_team()
{
	int	i;

	i = 0;
	while (i < _var()->nb_player / 2)
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
	
	_team()[TEAM_RED]->loose = 0;
	_team()[TEAM_RED]->win = 0;
	_team()[TEAM_RED]->team_spawn = posf(3, 3);
	i = 0;
	while (i < _var()->nb_player / 2)
	{
		_team()[TEAM_RED]->players[i] = _var()->red[i];
		i++;
	}
	_team()[TEAM_RED]->player_spawn[0] = posf(3, 3);
	_team()[TEAM_RED]->player_spawn[1] = posf(3, 4);
	_team()[TEAM_RED]->player_spawn[2] = posf(3, 2);

	_team()[TEAM_BLUE]->loose = 0;
	_team()[TEAM_BLUE]->win = 0;
	_team()[TEAM_BLUE]->team_spawn = posf(40, 9);
	i = 0;
	while (i < _var()->nb_player / 2)
	{
		_team()[TEAM_BLUE]->players[i] = _var()->blue[i];
		i++;
	}
	_team()[TEAM_BLUE]->player_spawn[0] = posf(40, 9);
	_team()[TEAM_BLUE]->player_spawn[1] = posf(40, 10);
	_team()[TEAM_BLUE]->player_spawn[2] = posf(41, 9);
	init_player_team();
}

// Coder Team update coté serveur