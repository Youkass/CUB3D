/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_lobby.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:56:16 by denissereno       #+#    #+#             */
<<<<<<<<< Temporary merge branch 1
/*   Updated: 2022/11/06 13:44:47 by yobougre         ###   ########.fr       */
=========
/*   Updated: 2022/11/05 17:03:25 by denissereno      ###   ########.fr       */
>>>>>>>>> Temporary merge branch 2
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
	//printf("linked : %d\n", _var()->linked_players);
	while (i < _var()->nb_player)
	{
		if (o_player.player[i].pseudo[0] != 0)
			_var()->o_player[i] = o_player.player[i];
		++i;
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
	{
		if (_var()->o_player[i].team == TEAM_BLUE)
		{
			_var()->blue[_var()->n_blue] = _var()->o_player[i].pseudo;
			++_var()->n_blue;
		}
		else if (_var()->o_player[i].team == TEAM_RED)
		{
			_var()->red[_var()->n_red] = _var()->o_player[i].pseudo;
			++_var()->n_red;
		}
		else
		{
			_var()->neutral[_var()->n_neutral] = _var()->o_player[i].pseudo;
			++_var()->n_neutral;
		}
		if (!(_image()->pseudo_img[i].img))
			_image()->pseudo_img[i] = create_text_img(_var()->o_player[i].pseudo, WHITE);
		i++;
	}
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
		exit (1); //TODO
	memset(&o_player, 0, sizeof(o_player));
	if (ft_recv_players(&o_player, sizeof(t_send_server)))
		exit (1); //TODO
	ft_copy_new_data(o_player);
}

void	menu_pong(void)
{
	get_pseudos();
}
