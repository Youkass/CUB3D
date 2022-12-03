/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_lobby.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:56:16 by denissereno       #+#    #+#             */
/*   Updated: 2022/12/03 20:00:56 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

/* ************************************************************************** */
/* besoin de faire une refonte totale de wait_lobby:
	# constement envoyer ses propres data et le tableau de player ensuite, verifier
		du cote server que toute les datas sont bien recu et ensuite bien envoye
	# ne plus envoyer linked_player seul, le faire dans une structure contenant
		1-tableau des joueurs et leurs data
		2-linked_player
		3-n'importe quel data utile */
/* ************************************************************************** */
static void	ft_cpy_tab(t_send_server o_player)
{
	int	i;

	i = 0;
	_var()->linked_players = o_player.linked_pl;
	while (i < _var()->linked_players)
	{
		if (o_player.player[i].pseudo[0] != 0)
			_var()->o_player[i] = o_player.player[i];
		++i;
	}
}

void	team_data(int i)
{
	t_data	txt;

	if (_var()->o_player[i].team == TEAM_BLUE)
	{
		_var()->blue[_var()->n_blue] = _var()->o_player[i].id;
		++_var()->n_blue;
	}
	else if (_var()->o_player[i].team == TEAM_RED)
	{
		_var()->red[_var()->n_red] = _var()->o_player[i].id;
		++_var()->n_red;
	}
	else
	{
		_var()->neutral[_var()->n_neutral] = _var()->o_player[i].id;
		++_var()->n_neutral;
	}
	if (!(_image()->pseudo_img[i].img))
	{
		txt = create_text_img(_var()->o_player[i].pseudo, WHITE);
		_image()->pseudo_img[i] = txt;
	}
}

static void	ft_copy_new_data(t_send_server o_player)
{
	int		i;

	memset(&_var()->o_player, 0, sizeof(_var()->o_player));
	ft_cpy_tab(o_player);
	if (o_player.start)
	{
		_var()->mode = GAME_START_ONLINE;
		_var()->started = 1;
	}
	_var()->n_blue = 0;
	_var()->n_red = 0;
	_var()->n_neutral = 0;
	i = 0;
	_player()->team = _var()->o_player[_player()->id].team;
	_player()->change_team = _var()->o_player[_player()->id].change_team;
	while (i < _var()->linked_players)
		team_data(i++);
}

void	get_pseudos(void)
{
	t_send_client	player;
	t_send_server	o_player;

	memset(&player, 0, sizeof(player));
	ft_copy_data_before_pong(&player.player);
	if (_player()->is_start)
		player.start = 1;
	else
		player.start = 0;
	player.flag = 1;
	if (send(_var()->socket, &player, sizeof(player), 0) < 0)
	{
		_var()->mode = MENU;
		_menu()->mode = MENU_START;
		return ;
	}
	memset(&o_player, 0, sizeof(o_player));
	if (ft_recv_players(&o_player, sizeof(t_send_server)))
	{
		_var()->mode = MENU;
		_menu()->mode = MENU_START;
		return ;
	}
	ft_copy_new_data(o_player);
}

void	menu_pong(void)
{
	get_pseudos();
	if (_player()->team == TEAM_RED)
	{
		_player()->x = _team()[TEAM_RED]->team_spawn.x;
		_player()->y = _team()[TEAM_RED]->team_spawn.y;
	}
	else if (_player()->team == TEAM_BLUE)
	{
		_player()->x = _team()[TEAM_BLUE]->team_spawn.x;
		_player()->y = _team()[TEAM_BLUE]->team_spawn.y;
	}
}
